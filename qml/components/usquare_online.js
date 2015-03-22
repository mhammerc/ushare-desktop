.pragma library
.import "network.js" as Network

var websocket; /* WebSocket QML element */
var wsRequestIsPending = false;
var wsRequestCallback = {};
var wsCallback = {}; //connected, closed, error

var _connected = false;

var _userInfo;
var _uploads;

var _username;
var _password;

var _accountKey;
var _privateKey;


/* If callback is false, then return already known data without refresh */
function getUserInfos(callback)
{
    if(!callback)
    {
        return _userInfo;
    }

    var onEnd = function(message, callback)
    {
        _userInfo = JSON.parse(message);
        callback(_userInfo);
    }


    var request = { path: '/user/info', accountKey: accountKey(),
        privateKey: privateKey() };

    wsSendTextMessage(JSON.stringify(request), onEnd, callback);
}

function getUploads(limit, callback)
{
    if(!callback)
    {
        return _uploads;
    }

    var onEnd = function (message, callback)
    {
        _uploads = JSON.parse(message);
        callback(_uploads);
    }

    var request = { path: '/user/uploads', limit: limit,
        accountKey: accountKey(), privateKey: privateKey() };

    wsSendTextMessage(JSON.stringify(request), onEnd, callback);
}

function connect(username, password, object, callback)
{
    _username = username;
    _password = password;

    var onEnd = function(err, result)
    {
        if(err !== null)
        {
            callback(err, result);
            return;
        }

        if(result.success)
        {
            _accountKey = result.accountKey;
            _privateKey = result.privateKey;
            initWebSocket(object);
            callback(err, result);
        } else {
            callback(err, result);
        }
    }

    Network.post("http://46.101.47.41/user/auth",
                 {username:_username, password:_password},
                 {},
                 onEnd);
}

/** WEBSOCKET **/

function wsSendTextMessage(message, callback, parametersToCallback)
{
    if(websocket.status !== 1)
        return;

    if(wsRequestIsPending)
        return;

    wsRequestIsPending = true;
    wsRequestCallback = { callback: callback, parameters: parametersToCallback };
    websocket.sendTextMessage(message);
}

function initWebSocket(object)
{
    var qmlString = 'import Qt.WebSockets 1.0; WebSocket {}'
    websocket = Qt.createQmlObject(qmlString, object);

    websocket.statusChanged.connect(wsStatusChanged);
    websocket.textMessageReceived.connect(wsMessageReceived);

    websocket.url = 'ws://46.101.47.41/';
}

function wsMessageReceived(message)
{
    wsRequestIsPending = false;
    wsRequestCallback.callback(message, wsRequestCallback.parameters);
}

function wsStatusChanged(status)
{
    if(status === 1) /* Connected */
    {
        _connected = true;

        if(typeof wsCallback.connected !== 'undefined')
            wsCallback.connected();
    }
    else if(status === 2) /* Closing */
    {
        _connected = false;

        if(typeof wsCallback.error !== 'undefined')
            wsCallback.error();
    }
    else if(status === 3) /* Closed */
    {
        _connected = false;

        if(typeof wsCallback.closed !== 'undefined')
            wsCallback.closed();
    }
    else if(status === 4) /* Error */
    {
        _connected = false;

        if(typeof wsCallback.error !== 'undefined')
            wsCallback.error();

        console.error('Websocket error : ' + websocket.errorString);
    }
}

function onWsConnected(callback)
{
    wsCallback.connected = callback;
}

function onWsError(callback)
{
    wsCallback.error = callback;
}

function onWsDisconnected(callback)
{
    wsCallback.closed = callback;
}

function deleteWebSocket()
{
    websocket.destroy();
}

/** GETTER */

function disconnect()
{
    deleteWebSocket();
    _connected = false;
    _userInfo = null;
    _username = null;
    _password = null;
    _accountKey = null;
    _privateKey = null;
}

function isConnected()
{
    return _connected;
}

function accountKey()
{
    return _accountKey;
}

function privateKey()
{
    return _privateKey;
}

function keys()
{
    return { accountKey: accountKey(), privateKey: privateKey() };
}

