import { appendFile } from "fs/promises";

await appendFile("database.log", "\n[3] database authorized", "utf8");