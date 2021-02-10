const express = require("express");
const fs = require("fs");
const multer = require("multer");
const rimraf = require("rimraf");
const path = require("path");
const chalk = require("chalk");

const { getFoldersDiff, scanDir } = require("../index");
const { assert } = require("console");

const port = 3000;
const tempUploadDir = path.join(__dirname, "temp_upload");
const storage = multer.diskStorage({
  destination: function (req, file, cb) {
    cb(null, tempUploadDir);
  },
  filename: function (req, file, cb) {
    cb(null, file.originalname);
  },
});
const upload = multer({ storage });

if (!fs.existsSync(tempUploadDir)) {
  fs.mkdirSync(tempUploadDir);
}

const app = express();
app.use(express.json());

app.post("/scan", (req, res) => {
  const target = path.join(__dirname, "prev");
  const map = req.body && req.body.map;

  if (!map) {
    res.status(400).send({
      error: "Error",
    });
    return;
  }

  console.log("Scanning " + target);

  const diff = getFoldersDiff(target, map);
  console.log("Scan finished, returning diff");
  res.send(diff);
  console.log("Diff returned");
});

app.post("/send_diff", upload.any(), (req, res) => {
  console.log("Applying diff");
  fs.readdirSync(path.join(__dirname, "next")).forEach((f) => {
    fs.copyFileSync(
      path.join(__dirname, "next", f),
      path.join(tempUploadDir, f)
    );
  });
  const should = JSON.stringify(scanDir(path.join(__dirname, "next")));
  const is = JSON.stringify(scanDir(tempUploadDir));

  assert(should === is, chalk.red("Folders are not equal after patch"));
  console.log(chalk.green("Folders are equal"));
  rimraf.sync(tempUploadDir);
  res.sendStatus(200);
  process.exit(0);
});

app.listen(port, () => {
  console.log(`Example app listening at http://localhost:${port}`);
});
