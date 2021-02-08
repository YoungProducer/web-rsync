const { getFoldersDiff } = require('../build/Release/file-checksum.node');
const http = require('http');
const express = require('express');
const multiparty = require('multiparty');

const { defaultPrefix, defaultRoutes } = require('./constants');

module.exports = { createServer };

function createServer(config) {
    const { protocol, host, port, routePrefix = defaultPrefix, routesMap } = config;

    const router = express.Router();

    const routesList = Object
        .entries({
            ...defaultRoutes,
            ...routesMap,
        })
        .reduce((acc, [key, value]) => ({
            ...acc,
            [key]: (routePrefix !== '/' ? '/' + routePrefix : '') + '/' + value,
        }), {});

    router.post(routesList.scan, (req, res) => {
        const target = req.body.target;
        const map = req.body.map;

        const diff = getFoldersDiff(target, map);

        res.json({ diff }).send();
    });

    router.post(routesList.send_diff, (req, res) => {
        console.log(req.files);
        // const form = new multiparty.Form();

        // form.parse(req, (err, fields, files) => {
        //     Object.keys(fields).forEach(function(name) {
        //         console.log('got field named ' + name);
        //     });
             
        //     Object.keys(files).forEach(function(name) {
        //         console.log('got file named ' + name);
        //     });
             
        //     console.log('Upload completed!');
        //     res.status(200).send('Received ' + files.length + ' files');
        // });
    })

    function getRouter() {
        return router;
    }

    return {
        getRouter,
    }
}
