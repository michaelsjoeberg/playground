const Eva = require("../Eva");
const Environment = require("../Environment");

const tests = [
    require("./self-eval-test.js"),
    require("./math-test.js"),
    require("./variables-test.js"),
    require("./block-test.js"),
    require("./if-test.js"),
    require("./while-test.js"),
    require("./built-in-function-test.js"),
    require("./user-defined-function-test.js"),
    require("./lambda-function-test.js"),
    require("./switch-test.js"),
    require("./for-test.js"),
    require("./inc-test.js"),
    require("./dec-test.js"),
    require("./class-test.js"),
    require("./module-test.js"),
    require("./import-test.js"),
];

const eva = new Eva();

tests.forEach(test => test(eva));

// eva.eval(["print", '"hello,"', '"eva"']);

console.log("all tests passed");
