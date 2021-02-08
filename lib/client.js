const { scanDir } = require('../build/Release/file-checksum.node'); 
const fetch = require('node-fetch');
const fs = require('fs');
const path = require('path');
const FormData = require('form-data');

const { defaultPrefix, defaultRoutes } = require('./constants');

module.exports = { createClient };

function createClient(config) {
    const {
        host,
        port,
        protocol,
        routePrefix = defaultPrefix,
        routesMap,
        prevLocation,
    } = config;

    let content;
    let url = protocol + '://' + host + ':' + port;
    let defaultPath = config.path;
    const routes = Object
        .entries({
            ...defaultRoutes,
            ...routesMap,
        })
        .reduce((acc, [key, value]) => ({
            ...acc,
            [key]: url + (routePrefix !== '/' ? '/' + routePrefix : '') + '/' + value,
        }), {});

    function scan(path) {
        content = scanDir(path || defaultPath);
        return content;
    }

    function sendScan(data, callback) {
        const map = data || content;
        const body = JSON.stringify({
            map,
            target: prevLocation,
        });

        fetch(routes.scan, {
            method: 'POST',
            mode: 'cors',
            cache: 'no-cache',
            credentials: 'same-origin',
            headers: {
              'Content-Type': 'application/json'
            },
            referrerPolicy: 'no-referrer',
            body
        })
        .then(res => {
            return callback(res.json(), null);
        })
        .catch(err => callback(null, err));
    }

    async function sendScanSync(data) {
        const map = data || content;
        const body = JSON.stringify({
            map,
            target: prevLocation,
        });

        const { diff } = await fetch(routes.scan, {
            method: 'POST',
            mode: 'cors',
            cache: 'no-cache',
            credentials: 'same-origin', // include, *same-origin, omit
            headers: {
              'Content-Type': 'application/json'
            },
            referrerPolicy: 'no-referrer', // no-referrer, *client
            body // body data type must match "Content-Type" header
        }).then(res => res.json());

        return diff;
    }

    function prepareFiles(diff, basePath = defaultPath) {
        const formData = new FormData();

        diff
            .filter(({ type }) => type !== 'REMOVE')
            .forEach((el) => {
                console.log(path.join(basePath, el.path))
                fs.readFile(path.join(basePath, el.path), (err, data) => {
                    if (err) {
                        console.log(err);
                    }

                    formData.append(el.path, data);
                });
            });

        return formData;
    }

    async function sendDiff(diff, basePath = defaultPath) {
        const data = prepareFiles(diff, basePath);

        return await sendPreparedDiff(data, basePath);
    }

    async function sendPreparedDiff(pDiff, basePath = defaultPath) {
        return await fetch(routes.send_diff, {
            method: 'POST',
            mode: 'cors',
            cache: 'no-cache',
            credentials: 'same-origin', // include, *same-origin, omit
            headers: {
              'Content-Type': 'multipart/form-data'
            },
            referrerPolicy: 'no-referrer', // no-referrer, *client
            body: pDiff,
        })
    }

    return {
        scan,
        sendScan,
        sendScanSync,
        prepareFiles,
        sendDiff,
        sendPreparedDiff
    };
}