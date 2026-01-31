import { readFileSync } from "fs";

const data = readFileSync("code.bin", "utf8");
console.log(data);