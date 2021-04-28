var arraysOfWords = [
    [
        "appropriately", "assertively", "authoritatively", "collaboratively", "compellingly", "competently", "completely", "continually", "conveniently", "credibly", "distinctively", "dramatically", "dynamically"
    ],
    [
        "actualize", "administrate", "aggregate", "architect", "benchmark", "brand", "build", "cloudify", "communicate", "conceptualize", "coordinate", "create", "cultivate"
    ],
    [
        "24/7", "24/365", "accurate", "adaptive", "agile", "alternative", "an expanded array of", "B2B", "B2C", "backend", "backward-compatible", "best-of-breed", "bleeding-edge"
    ],
    [
        "action items", "adoption", "alignments", "applications", "architectures", "bandwidth", "benefits", "best practices", "catalysts for change", "channels", "clouds", "collaboration and idea-sharing", "communities"
    ]
];

function writeToHTML() {
    for (var i = 0; i < 4; i++) {
        for (var j = 0; j < arraysOfWords[i].length; j++) {
            $("#" + i.toString()).append(arraysOfWords[i][j] + "<br>")
        }
    }
}

$(document).ready(function () {
    writeToHTML();
})

$('#generate').click(function () {
    var randomBs = "";
    for (array of arraysOfWords) {
        randomBs += array[Math.floor(Math.random() * array.length)] + " ";
    }
    $('#result').val(randomBs);
})