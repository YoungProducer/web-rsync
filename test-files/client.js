const fetch = require("node-fetch");
const fs = require("fs");
const path = require("path");
const FormData = require("form-data");

const { scanDir } = require("../index");

const api = "http://localhost:3000/";
const defaultPath = path.join(__dirname, "next");

/**
 *
 * @param {string} path
 */
function scan(path) {
  let content = scanDir(path);
  return content;
}

/**
 *
 * @param {import("../index").FilesMap} data
 * @returns {Promise<object>}
 */
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

/**
 *
 * @param {import("../index").FileAction[]} diff
 * @param {string} basePath
 */
function prepareFiles(diff, basePath = defaultPath) {
  const formData = new FormData();

  diff
    .filter(({ type }) => type !== "REMOVE")
    .forEach((el) => {
      const filePath = path.join(basePath, el.path);
      const data = fs.createReadStream(filePath);
      formData.append(el.path, data);
    });

  return formData;
}

/**
 *
 * @param {FormData} pDiff
 * @param {string} basePath
 */
function sendPreparedDiff(pDiff, basePath = defaultPath) {
  console.log("Sending diff");
  return fetch(api + "send_diff", {
    method: "POST",
    mode: "cors",
    cache: "no-cache",
    credentials: "same-origin", // include, *same-origin, omit
    headers: pDiff.getHeaders(),
    referrerPolicy: "no-referrer", // no-referrer, *client
    body: pDiff,
  });
}

const s = scan(path.join(__dirname, "next"));

sendScanSync(s)
  .then((res) => {
    console.log("Preparing files");
    const data = prepareFiles(res);
    console.log("Prepared files");
    return sendPreparedDiff(data);
  })
  .then((res) => {
    console.log("Sent diff");
  });
