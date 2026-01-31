import { writeFile } from "fs/promises";

await writeFile("database.log", "[1] database created", "utf8");
