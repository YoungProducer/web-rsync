const express = require("express");
const bodyParser = require("body-parser");

const { getFoldersDiff } = require("../index");

const app = express();
app.use(bodyParser.json());
app.use(bodyParser.urlencoded({ extended: true }));
const port = 3000;

app.listen(port, () => {
  console.log(`Example app listening at http://localhost:${port}`);
});

app.post("/scan", (req, res) => {
  const target = "/Users/leon/dev/web-rsync/test-files/next";
  const map = req.body.map;

  const diff = getFoldersDiff(target, map);
  res.send(diff);
});

app.post("/send_diff", (req, res) => {
  console.log(req.files);
  console.log(req.body);
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
});
