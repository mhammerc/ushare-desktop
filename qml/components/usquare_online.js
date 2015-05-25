.pragma library
.import "network.js" as Network
.import U.Global 1.0 as Global

var websocket; /* WebSocket QML element */
var wsRequestIsPending = false;
var wsRequestCallback = {};
var wsCallback = {}; //connected, closed, error

var sourceName = 'uShare-dev'

var _connected = false;

var _userInfo;
var _uploads;

var _username;
var _password;
var _email;

var _accountKey;
var _privateKey;

var Settings;

function setSettings(s)
{
    Settings = s;
}

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
    var onEnd = function(message)
    {
        _uploads = JSON.parse(message);
        callback(_uploads);
    }

    var request = { path: '/user/uploads', limit: limit, };

    wsSendTextMessage(JSON.stringify(request), onEnd);
}

function editFilePassword(newPassword, shortName, callback)
{
    var onEnd = function(err, result)
    {
        console.log(Settings.editPasswordUrl);
        callback(err, JSON.parse(result));
    }

    console.log(_accountKey + '+' + _privateKey);

    Network.post(Settings.editPasswordUrl, {
                     accountkey: _accountKey,
                     privatekey: _privateKey,
                     password: newPassword,
                     shortname: shortName,
                     source: sourceName, }, {}, onEnd);
}

function deleteFile(shortName, callback)
{
    var onEnd = function(err, result)
    {
        callback(err, JSON.parse(result));
    }

    Network.post(Settings.deleteUrl, {
                     accountkey: _accountKey,
                     privatekey: _privateKey,
                     shortname: shortName,
                     source: sourceName }, {}, onEnd);
}

function connect(username, password, callback)
{
    _username = username;
    _password = password;

    var onEnd = function(err, result)
    {
        try
        {
            result = JSON.parse(result);
        } catch(e) {
            callback(true, null);
            return;
        }

        if(err !== null)
        {
            callback(err, result);
            return;
        }

        if(result.success)
        {
            _accountKey = result.accountkey;
            _privateKey = result.privatekey;

            callback(err, result);
        }
        else
        {
            callback(err, result);
        }
    };

    Network.post(Settings.authUrl,
                 { username: _username, password: _password, source: sourceName },
                 {},
                 onEnd);
}

function register(username, password, email, callback)
{
    _username = username;
    _password = password;
    _email = email;

    var onEndRegister = function(err, result)
    {
        result = JSON.parse(result);

        if(err !== null)
        {
            callback(err, result);
            return;
        }

        if(result.success)
        {
            connect(_username, _password, callback);
        }
        else
        {
            callback(err, result);
        }
    };

    Network.post(Settings.registerUrl,
                { username: _username, password: _password, email: _email, source: sourceName }, {}, onEndRegister);
}

/** WEBSOCKET **/

function wsSendTextMessage(message, callback, parametersToCallback)
{
    if(!_connected)
        return;

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
    var qmlString = 'import Qt.WebSockets 1.0; WebSocket {}';
    websocket = Qt.createQmlObject(qmlString, object);

    websocket.statusChanged.connect(wsStatusChanged);
    websocket.textMessageReceived.connect(wsMessageReceived);

    websocket.url = Settings.wsUrl;
}

function wsAuth(callback)
{
    var object = {};
    object.path = "/user/auth";
    object.username = _username;
    object.password = _password;
    object.source = sourceName;

    wsSendTextMessage(JSON.stringify(object), function(result) { callback(JSON.parse(result)); });
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

