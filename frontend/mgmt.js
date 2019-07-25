const http = require("http")

class TransmissionInterface {
	requestServer(requestObj, responseHandler) {
		const opts = {
			host: "127.0.0.1",
			path: "/transmission/rpc/",
			method: "POST",
			headers: {
				"X-Transmission-Session-Id": "njY0fT4q76bYE3mS6tQApqXqLNlsYdpWjGryCAcwvAs81Z67"
			},
		}
		var req = http.request(opts, result => {
			var responseStr = ""
			result.on("data", data => {
				responseStr += data
			})
			result.on("end", () => {
				const response = JSON.parse(responseStr)
				if (response.result != "success")
					console.error("ERROR: Non-success from server")
				else
					responseHandler(response)
			})
		})
		req.write(JSON.stringify(requestObj))
		req.end()
	}

	availableMemory(responseHandler) {
		const reqObj = {
			"method": "free-space",
			"arguments": {
				path: "/root/Downloads/",
			},
		}
		requestServer(reqObj, result => {
			const nRemaining = result.arguments["size-bytes"]
			responseHandler(nRemaining)
		})
	}

	getAllTorrents(responseHandler) {
		const reqObj = {
			"method": "torrent-get",
			"arguments": {
				fields: [
					"files",
					"eta",
					"name",
					"rateDownload",
					"id",
					"downloadDir",
				],
			},
		}
		this.requestServer(reqObj, result => {
			const torrentList = result.arguments.torrents
			const isMovieFile = file => {
				return ["mp4", "avi", "mkv", "mpg", "3gp"].some(
					ext => file.name.endsWith("." + ext)
				)
			}
			const isFileComplete = file => file.bytesCompleted === file.length
			const areFilesComplete = files => files.every(isFileComplete)
			const totalDownloaded = files =>
				files
					.map(file => file.bytesCompleted)
					.reduce((a, b) => a + b, 0)
			const total = files =>
				files
					.map(file => file.length)
					.reduce((a, b) => a + b, 0)
			responseHandler(torrentList.map(torrent => {
				const files = torrent.files
				const progress = 100*totalDownloaded(files)/total(files)
				return {
					id: torrent.id,
					name: torrent.name,
					eta: torrent.eta,
					speed: torrent.rateDownload,
					progress: parseFloat(progress.toFixed(2)) + "%",
					complete: files.every(isFileComplete),
					downloadPath: torrent.downloadDir,
				}
			}))
		})
	}

	startDownload(maglink) {
		const reqObj = {
			"method": "torrent-add",
			"arguments": {
				filename: maglink,
			},
		}
		this.requestServer(reqObj, result => {
			console.log(result)
		})
	}

	pauseDownload(id) {
		const reqObj = {
			"method": "torrent-stop",
			"arguments": { ids: id },
		}
		this.requestServer(reqObj, result => {
			console.log(result)
		})
	}

	deleteFile(id) {
		const reqObj = {
			"method": "torrent-remove",
			"arguments": {
				ids: id,
				"delete-local-data": true,
			},
		}
		this.requestServer(reqObj, result => {
			console.log(result)
		})
	}

	getTorrentPropertiesByName(name, propertyExtractor, propertiesHandler) {
		getAllTorrents(torrents => {
			const properties = torrents
				.filter(torrent => torrent.name === name)
				.map(propertyExtractor)
			propertiesHandler(properties)
		})
	}

	getProgressesByName(name, progressHandler) {
		getTorrentPropertiesByName(name, torrent => torrent.progress, progressHandler)
	}

	getIdsByName(name, idHandler) {
		getTorrentPropertiesByName(name, torrent => torrent.id, idHandler)
	}

	getETAsByName(name, etaHandler) {
		getTorrentPropertiesByName(name, torrent => torrent.eta, etaHandler)
	}

	getDownloadDirectoryByName(name, dirHandler) {
		getTorrentPropertiesByName(name, torrent => torrent.downloadPath, dirHandler)
	}
}


ti = new TransmissionInterface()
ti.getAllTorrents(torrents => { console.log(torrents) })
