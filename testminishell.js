/* ************************************************************************** */
/*                                                                            */
/*                Created with love by:               Mohamed Dahani          */
/*                                                                            */
/* ************************************************************************** */

const path = require("path");
const { spawnSync } = require("child_process");
const fs = require("fs");

const minishellPath = "./minishell";
// Make sure to change the program name variable if you have a different one and make sure to write him correctly
const programName = "minishell$> ";
const logDir = "./logs";
const testOutput = path.join(logDir, "test_output.txt");
const refOutput = path.join(logDir, "bash_output.txt");
let errorStatus = false;
let commandFailled = [];

// Add your test commands here
const tests = [
    "echo $USER'$USER'$USER",
    "ls $a",
    "export a=lsss && $a",
  ];
  

const runCommand = (shell, command) => {
  try {
    const result = spawnSync(shell, [], {
      input: command,
      encoding: "utf-8",
      shell: false,
    });
    return result.stdout;
  } catch (error) {
    return `Error: ${error.message}`;
  }
};

const comparisonCommands = (command) => {
  const bashOutput = runCommand("bash", command);
  let minishellOutput = runCommand(minishellPath, command)
    .replace(programName, "")
    .replace("\n", "")
    .replace(programName, "")
    .replace(command, "");
  fs.writeFileSync(refOutput, bashOutput);
  fs.writeFileSync(testOutput, minishellOutput);
  if (bashOutput !== minishellOutput) {
    console.log(`\x1b[31m[FAIL]\x1b[0m Command: ${command}`);
    printDiff(bashOutput, minishellOutput);
    commandFailled.push(command);
    errorStatus = true;
  } else {
    console.log(`\x1b[32m[OK]\x1b[0m   Command: ${command}`);
  }
};

const printDiff = (expected, actual) => {
  const expectedLines = expected.split("\n");
  const actualLines = actual.split("\n");

  for (let i = 0; i < expectedLines.length; i++) {
    if (expectedLines[i] !== actualLines[i]) {
      console.log(`\x1b[33m- Bash:      ${expectedLines[i] || "<empty>"}`);
      console.log(`+ Minishell: ${actualLines[i] || "<empty>"}\x1b[0m`);
    }
  }
};

const runTests = () => {
  if (!fs.existsSync(minishellPath)) {
    console.log(
      "\n\x1b[1m\x1b[31m❌ ./minishell not found. Make sure it is compiled.\x1b[0m\n"
    );
    process.exit(1);
  }
  fs.mkdirSync(logDir, { recursive: true });
  console.log("\n\x1b[1m\x1b[37m🐚 Running Minishell tests...\x1b[0m\n");
  for (const command of tests) {
    comparisonCommands(command);
  }

  console.log("\n\x1b[1m\x1b[37m🧪 Testing complete.\x1b[0m\n");

  if (errorStatus) {
    console.log(
      "\x1b[31m\x1b[1m╭─────────────────────────────────────────────────╮"
    );
    console.log(
      "\x1b[31m\x1b[1m│  ❌ tests failed. Please check the logs!        │"
    );
    console.log(
      "\x1b[31m\x1b[1m╰─────────────────────────────────────────────────╯\x1b[0m"
    );
    console.log("\n\x1b[1m\x1b[37m🚨 The command that failed:\x1b[0m\n")
    for (let i = 0; i < commandFailled.length; i++) {
        console.log(`\x1b[31m${commandFailled[i]}\x1b[1m`);
    }
  } else {
    console.log("\x1b[32m\x1b[1m╭──────────────────────────────╮");
    console.log("\x1b[1m│  ✅ All tests passed!        │");
    console.log("\x1b[32m╰──────────────────────────────╯\x1b[0m");
  }
  console.log(
    "\n\x1b[4m\x1b[34mCreated with love by: Mohamed Dahani ❤️\x1b[0m\n"
  );
};

runTests();