const input = Deno.args[0];
const output = input.split(".")[0] + ".sus.c";

let code = Deno.readTextFileSync(input);

code = "#include <amogus.h>\n" + code;

code = code.replaceAll("{", "amogus");
code = code.replaceAll("}", "sugoma");

code = code.replaceAll("==", "be");
code = code.replaceAll("!=", "notbe");
code = code.replaceAll("<=", "lesschungus");
code = code.replaceAll(">=", "morechungus");
code = code.replaceAll("+=", "grow");
code = code.replaceAll("-=", "shrink");
code = code.replaceAll("|=", "merge");

code = code.replaceAll("true", "straight");
code = code.replaceAll("false", "gay");

code = code.replaceAll("case", "casus maximus");

code = code.replaceAll("main", "gangster");

code = code.replaceAll("=", "eats");

code = code.replaceAll(";", " fr");
code = code.replaceAll("return", "get the fuck out");

code = code.replaceAll("__attribute__((__packed__))", "chungus");
code = code.replaceAll("__attribute__((__naked__))", "strip");


Deno.writeTextFileSync(output, code);