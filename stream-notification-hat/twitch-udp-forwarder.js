const dgram = require('dgram');
const server = dgram.createSocket('udp4');
const io = require('socket.io-client');
const tmi = require('tmi.js');

const udpBroadcast = "YOUR LOCAL BROADCAST IP (i.e. 192.168.1.255)";
const socketToken = 'YOUR STREAMLABS SOCKET TOKEN';
const port = 4577;
const channel = "mikesci"; // the twitch channel to monitor for chat events

/* convert a hex character to an integer */
function hexVal(character) {
    if (character.length != 1) { return 0; }
    if (character == "a") { return 10; }
    if (character == "b") { return 11; }
    if (character == "c") { return 12; }
    if (character == "d") { return 13; }
    if (character == "e") { return 14; }
    if (character == "f") { return 15; }
    let num = parseInt(character);
    return (isNaN(num) ? 0 : num);
}

/* connect to twitch and monitor for messages */
var conn = new tmi.client({
    connection: { secure: false },
    options: { debug: false },
    channels: [ channel ]
});

conn.addListener('message', function (channel, user, message, self) {
    if (user.color) {
        // convert a users color to an RGB triplet
        var hexString = user.color.substring(1).toLowerCase();
        var r = (hexVal(hexString[0]) * 16) + hexVal(hexString[1]);
        var g = (hexVal(hexString[2]) * 16) + hexVal(hexString[3]);
        var b = (hexVal(hexString[4]) * 16) + hexVal(hexString[5]);
        broadcastPayload(getChatPayload(r, g, b));
    }
});

conn.connect();

/* payload generators */
function getSubscribePayload() { return new Uint8Array([1]); }
function getBitsPayload() { return new Uint8Array([2]); }
function getDonationPayload() { return new Uint8Array([3]); }
function getRaidPayload() { return new Uint8Array([4]); }
//function getGiftPayload() { return new Uint8Array([5]); }
function getFollowPayload() { return new Uint8Array([6]); }
function getChatPayload(r, g, b) { return new Uint8Array([7, r, g, b]); }

function broadcastPayload(payload) {
    server.send(payload, port, udpBroadcast);
}

/* connect to streamlabs and monitor for events */
const streamlabs = io(`https://sockets.streamlabs.com?token=${socketToken}`);
streamlabs.on('event', (eventData) => {
    console.log(eventData);
    if (eventData.type === 'donation') {
        for(var i = 0; i < eventData.message.length; i++) {
            broadcastPayload(getDonationPayload());
        }
    }
    if (eventData.for === 'twitch_account') {
        switch(eventData.type) {
            case 'follow':
                for(var i = 0; i < eventData.message.length; i++) { broadcastPayload(getFollowPayload()); }
                break;
            case 'raid':
                for(var i = 0; i < eventData.message.length; i++) { broadcastPayload(getRaidPayload()); }
                break;
            case 'bits':
                for(var i = 0; i < eventData.message.length; i++) { broadcastPayload(getBitsPayload()); }
                break;
            case "resub":
            case 'subscription':
                for(var i = 0; i < eventData.message.length; i++) { broadcastPayload(getSubscribePayload()); }
                break;
            default:
                break;
        }
    }
});