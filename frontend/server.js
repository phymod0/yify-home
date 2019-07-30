var http = require('http'),
    fileSystem = require('fs'),
    path = require('path');

http.createServer(function(request, response) {
	const getMimeType = (fileName) => {
		const split = fileName.split('.');
		const ext = split[split.length - 1]
        const knownVideoMimes = ["mp4", "avi", "mkv", "mpg", "3gp"]
        if (knownVideoMimes.some(ext => fileName.endsWith('.' + ext)))
            return 'video/' + ext
        if (fileName.endsWith(".js"))
            return 'text/javascript'
		return "text/html"
	}

	try {
		var filePath = decodeURIComponent(request.url.split("localhost"))
        if (!filePath.startsWith("/root"))
            // Relative path
            filePath = "." + filePath
		var stat = fileSystem.statSync(filePath)
		console.log("Got a request for " + filePath)
	} catch {
		console.log(`File at ${filePath} not found...`)
		return
	}

    response.writeHead(200, {
        'Content-Type': getMimeType(filePath),
        'Content-Length': stat.size
    });

    var readStream = fileSystem.createReadStream(filePath);
    readStream.pipe(response);
})
.listen(80);
