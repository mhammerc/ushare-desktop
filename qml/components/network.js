.pragma library

/* url : the url to send request
 * headers : {key:value,..}
 * success : callback if the request success
 * error : callback if the request error
 */
function get(url, headers, callback)
{
    var req = new XMLHttpRequest();
    req.open('get', url, true);

    for(var property in headers)
    {
        req.setRequestHeader(property, headers[property]);
    }

    req.onreadystatechange = function()
    {
        if(req.readyState === XMLHttpRequest.DONE)
        {
            //console.log('Status : ', req.status);
            //console.log('Response : ', req.responseText);

            if(req.status == 200) {
                callback(null, req.responseText);
            } else {
                callback(req.status, req.responseText);
            }
        }
    }

    req.send();
}

function post(url, form, headers, callback)
{
    var req = new XMLHttpRequest();
    req.open('post', url);

    var formData = '';

    for(var property in form)
    {
        var value = form[property];
        formData +=
                property + '=' +
                value + '&'
    }

    formData += 'from=uapp'

    req.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");

    for(var property in headers)
    {
        req.setRequestHeader(property, headers[property]);
    }

    req.onreadystatechange = function()
    {
        if(req.readyState === XMLHttpRequest.DONE)
        {
            var status = req.status;

            console.log('Status : ', req.status);
            console.log('Response : ', req.responseText);

            if(status == 200) {
                callback(null, req.responseText);
            } else {
                callback(status, req.responseText);
            }
        }
    }

    req.send(formData);
}

function gravatar(email, md5, callback)
{
    email = email.toLowerCase();
    email = md5(email);

    var url = 'http://www.gravatar.com/' + email + '.json';

    get(url, {}, function(err, response)
    {
        if(err !== null)
        {
            callback(null)
            return;
        }

        response = JSON.parse(response);

        var url = response.entry[0].thumbnailUrl;

        callback(url);
    });
}

