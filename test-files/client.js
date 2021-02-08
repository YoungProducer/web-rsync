const fetch = require("node-fetch");
const fs = require("fs");
const path = require("path");
const FormData = require("form-data");

const { scanDir } = require("../index");

const api = "http://localhost:3000/";
const defaultPath = "/Users/leon/dev/web-rsync/test-files/prev";

function scan(path) {
  let content = scanDir(path);
  return content;
}

function sendScan(data, callback) {
  const map = data || content;
  const body = JSON.stringify({
    map,
    target: prevLocation,
  });

  fetch(api + "scan", {
    method: "POST",
    mode: "cors",
    cache: "no-cache",
    credentials: "same-origin",
    headers: {
      "Content-Type": "application/json",
    },
    referrerPolicy: "no-referrer",
    body,
  })
    .then((res) => {
      return callback(res.json(), null);
    })
    .catch((err) => callback(null, err));
}

function sendScanSync(data) {
  const map = data;
  const body = JSON.stringify({
    map,
  });

  return fetch(api + "scan", {
    method: "POST",
    mode: "cors",
    cache: "no-cache",
    credentials: "same-origin", // include, *same-origin, omit
    headers: {
      "Content-Type": "application/json",
    },
    referrerPolicy: "no-referrer", // no-referrer, *client
    body, // body data type must match "Content-Type" header
  }).then((res) => res.json());
}

function prepareFiles(diff, basePath = defaultPath) {
  const formData = new FormData();

  diff
    .filter(({ type }) => type !== "REMOVE")
    .forEach((el) => {
      console.log(path.join(basePath, el.path));
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

function sendPreparedDiff(pDiff, basePath = defaultPath) {
  return fetch(api + "send_diff", {
    method: "POST",
    mode: "cors",
    cache: "no-cache",
    credentials: "same-origin", // include, *same-origin, omit
    headers: {
      "Content-Type": "multipart/form-data",
    },
    referrerPolicy: "no-referrer", // no-referrer, *client
    body: pDiff,
  });
}

const s = scan("/Users/leon/dev/web-rsync/test-files/prev");
console.log({ scan: s });

sendScanSync(s)
  .then((res) => {
    console.log({ res });
    const data = prepareFiles(res);
    return sendPreparedDiff(data);
  })
  .then((res) => {
    console.log(res);
  });
