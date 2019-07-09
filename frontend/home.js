'use strict';

const e = React.createElement;


const colors = {
	green: "#00FF00",
	blue: "#008070",
	red: "#FF0000",
	cyan: "#00FFFF",
	yellow: "#FFFF00",
	magenta: "#FF00FF",
	grey: "#282828",
	lightgrey: "#484848",
	white: "#FFFFFF",
	black: "#000000",
}


class SearchQuery {
	constructor(props) {
		this.state = {
			queryTerm: "",
			minRating: 0,
			genre: "",
			orderBy: "",
			pageNum: 1,
		}
	}

	getQueryTerm() { return this.state.queryTerm }
	getMinRating() { return this.state.minRating }
	getGenre() { return this.state.genre }
	getOrder() { return this.state.orderBy }

	setQueryTerm(term) { this.state.queryTerm = term }
	setMinRating(rating) { this.state.minRating = rating }
	setGenre(genre) { this.state.genre = genre }
	setOrder(order) { this.state.orderBy = order }

	jumpPageNum(jump) {
		if (this.state.pageNum + jump > 0)
			this.state.pageNum += jump
		else
			this.state.pageNum = 1
	}
	resetPageNum() {
		this.state.pageNum = 1
	}
	isFirstPage() {
		return this.state.pageNum == 1
	}

	getPage(renderPage, reportError) {
		let init = "https://yts.lt/api/v2/list_movies.json?limit=16"
		if (this.state.pageNum)
			init += "&page=" + this.state.pageNum
		if (this.state.queryTerm)
			init += "&query_term=" + this.state.queryTerm
		if (this.state.minRating)
			init += "&minimum_rating=" + this.state.minRating
		if (this.state.genre)
			init += "&genre=" + this.state.genre
		if (this.state.orderBy) {
			let add = this.state.orderBy
			if (add == "Upload date")
				add = "date_added"
			init += "&sort_by=" + add
		}

		fetch(init)
		.then(res => res.json())
		.then(
			res => { renderPage(res) },
			err => { reportError(err) },
		)
	}
}

class DropDownSelectorTitleFrame extends React.Component {
	constructor(props) {
		super(props)
		this.state = {
			mouseOver: false,
		}
	}

	getStyle() {
		const color = this.props.color
		const outset = this.props.open ? 8 : this.state.mouseOver ? 5 : 2
		return {
			width: "90%",
			height: "100%",
			textAlign: "center",
			border: `1px solid ${color}`,
			backgroundColor: colors.lightgrey,
			borderRadius: "3px",
			WebkitBoxShadow: `0px 0px ${outset}px ${color}`,
			boxShadow: `0px 0px ${outset}px ${color}`,
			color: colors.white,
			cursor: "pointer",
		}
	}

	render() {
		const selected = this.props.selectorState.selected
		const title = selected ? selected : this.props.defaultTitle
		return e(
			'button',
			{
				style: this.getStyle(),
				onClick: this.props.toggler,
				onMouseOver: () => { this.setState({mouseOver: true}) },
				onMouseOut: () => { this.setState({mouseOver: false}) },
			},
			title,
		)
	}
}

class DropDownSelectorItemsFrame extends React.Component {
	constructor(props) {
		super(props)
		this.renderItem = this.renderItem.bind(this)
	}

	getStyle() {
		const color = this.props.color
		const outset = 7
		return {
			padding: "5px",
			textAlign: "center",
			backgroundColor: colors.lightgrey,
			border: `1px solid ${color}`,
			borderRadius: "3px",
			WebkitBoxShadow: `0px 0px ${outset}px ${color}`,
			boxShadow: `0px 0px ${outset}px ${color}`,
			color: colors.white,
			listStyle: "none",
			position: "relative",
			zIndex: 1,
			cursor: "pointer",
		}
	}

	renderItem(item, idx) {
		const selected = idx == this.props.selectorState.selectedIdx
		const selectNewItem = this.props.selecter
		const color = idx == 0 ? colors.lightgrey : colors.grey
		return e(
			'li',
			{
				style: {
					textAlign: "center",
					borderTop: `1px solid ${color}`,
				},
				onClick: () => { selectNewItem(item, idx) },
				key: idx,
			},
			item,
		)
	}

	render() {
		return e(
			'ul',
			{style: this.getStyle()},
			this.props.itemList.map(this.renderItem)
		)
	}
}

class DropDownSelector extends React.Component {
	constructor(props) {
		super(props)
		this.state = {
			selected: "",
			selectedIdx: -1,
		}
		this.toggleDropDown = this.toggleDropDown.bind(this)
		this.selectNewItem = this.selectNewItem.bind(this)
	}

	getStyle() {
		return {
			float: "left",
			textAlign: "center",
			height: "100%",
			flexGrow: 1,
		}
	}

	toggleDropDown() {
		this.props.toggler()
	}

	selectNewItem(item, itemIdx) {
		this.state.selected = item
		this.state.selectedIdx = itemIdx
		this.props.setSearchAttribute(item)
		this.props.toggler()
	}

	render() {
		const defaultTitle = this.props.defaultTitle
		const itemList = this.props.itemList
		return e(
			'div',
			{
				style: this.getStyle(),
			},
			e(DropDownSelectorTitleFrame, {
				selectorState: this.state,
				defaultTitle: defaultTitle,
				color: this.props.color,
				toggler: this.toggleDropDown,
				open: this.props.open,
			}),
			this.props.open ? e(DropDownSelectorItemsFrame, {
				selectorState: this.state,
				itemList: itemList,
				color: this.props.color,
				selecter: this.selectNewItem,
			}) : null,
		)
	}
}

class ConstraintPanel extends React.Component {
	constructor(props) {
		super(props)
		this.state = {
			selectedIdx: -1
		}
		this.dropDownToggler = this.dropDownToggler.bind(this)
		this.createDropDown = this.createDropDown.bind(this)
		this.attributeSetter = this.attributeSetter.bind(this)
	}

	dropDownToggler(idx) {
		const toggler = () => {
			const select = this.state.selectedIdx
			const newSelect = select == idx ? -1 : idx
			this.setState({
				selectedIdx: select == idx ? -1 : idx,
			})
		}
		return toggler.bind(this)
	}

	getStyle() {
		return {
			width: "30%",
			height: "0.45in",
			padding: "0.1in",
			display: "flex",
			justifyContent: "space-evenly",
			textAlign: "center",
			margin: "auto",
		}
	}

	attributeSetter(titleIdx) {
		return [
			(attribute) => {
				const attrlen = attribute.length
				attribute = attribute.substring(0, attrlen - 1)
				const minRating = parseInt(attribute)
				this.props.searchQuery.setMinRating(minRating)
			},
			(attribute) => {
				this.props.searchQuery.setGenre(attribute)
			},
			(attribute) => {
				this.props.searchQuery.setOrder(attribute)
			},
		][titleIdx].bind(this)
	}

	createDropDown(menu, idx) {
		const title = menu[0]
		const items = menu[1]
		return e(
			DropDownSelector,
			{
				defaultTitle: title,
				itemList: items,
				color: this.props.color,
				open: idx == this.state.selectedIdx,
				key: idx,
				toggler: this.dropDownToggler(idx),
				setSearchAttribute: this.attributeSetter(idx)
			},
		)
	}

	render() {
		const color = this.props.color
		const menu = [
			["Rating", ["1+", "2+", "3+", "4+", "5+", "6+", "7+", "8+", "9+"]],
			["Genre", ["Comedy", "Horror", "Mystery", "Action", "Thriller"]],
			["Sort by", ["Year", "Rating", "Upload date", "Title"]],
		]
		return e(
			'div',
			{style: this.getStyle()},
			menu.map(this.createDropDown),
		)
	}
}

class PageJumper extends React.Component {
	constructor(props) {
		super(props)
		this.state = {
			focused: false,
		}
		this.onClickHandler = this.onClickHandler.bind(this)
	}

	getStyle() {
		const color = this.props.color
		const outset = this.state.focused ? 7 : 2
		return {
			width: "8%",
			height: "100%",
			backgroundColor: colors.lightgrey,
			border: `1px solid ${color}`,
			borderRadius: "3px",
			padding: "10px",
			float: "left",
			WebkitBoxShadow: `0px 0px ${outset}px ${color}`,
			boxShadow: `0px 0px ${outset}px ${color}`,
			color: colors.white,
			cursor: "pointer",
		}
	}

	onClickHandler() {
		this.props.setPending()
		const searchQuery = this.props.searchQuery
		searchQuery.jumpPageNum(this.props.jump)
		searchQuery.getPage(
			json => { this.props.resultHandler(json.data.movies) },
			err => { this.props.errorHandler(err) },
		)
	}

	render() {
		return e(
			'input',
			{
				type: "submit",
				style: this.getStyle(),
				value: this.props.icon,
				onMouseOver: () => {this.setState({focused: true})},
				onMouseOut: () => {this.setState({focused: false})},
				onClick: this.onClickHandler,
			},
		)
	}
}

class SearchButton extends React.Component {
	constructor(props) {
		super(props)
		this.state = {
			focused: false,
		}
		this.onClickHandler = this.onClickHandler.bind(this)
	}

	getStyle() {
		const color = this.props.color
		const outset = this.state.focused ? 7 : 2
		return {
			width: "14%",
			height: "100%",
			backgroundColor: colors.lightgrey,
			border: `1px solid ${color}`,
			borderRadius: "3px",
			padding: "10px",
			float: "left",
			WebkitBoxShadow: `0px 0px ${outset}px ${color}`,
			boxShadow: `0px 0px ${outset}px ${color}`,
			color: colors.white,
			cursor: "pointer",
		}
	}

	onClickHandler() {
		this.props.setPending()
		const searchQuery = this.props.searchQuery
		searchQuery.resetPageNum()
		searchQuery.getPage(
			json => { this.props.resultHandler(json.data.movies) },
			err => { this.props.errorHandler(err) },
		)
	}

	render() {
		return e(
			'input',
			{
				type: "submit",
				style: this.getStyle(),
				value: "Search",
				onMouseOver: () => {this.setState({focused: true})},
				onMouseOut: () => {this.setState({focused: false})},
				onClick: this.onClickHandler,
			},
		)
	}
}

class QueryBar extends React.Component {
	constructor(props) {
		super(props)
		this.state = {
			focused: false,
		}
	}

	getStyle() {
		const color = this.props.color
		const inset = this.state.focused ? 15 : 5
		return {
			width: "60%",
			height: "100%",
			backgroundColor: colors.lightgrey,
			border: `1px solid ${color}`,
			borderRadius: "3px",
			padding: "10px",
			float: "left",
			WebkitBoxShadow: `inset 0px 0px ${inset}px ${color}`,
			boxShadow: `inset 0px 0px ${inset}px ${color}`,
			color: colors.white,
		}
	}

	render() {
		return e(
			'input',
			{
				type: "text",
				style: this.getStyle(),
				placeholder: "Keyword",
				onFocus: () => {this.setState({focused: true})},
				onBlur: () => {this.setState({focused: false})},
				onChange: (ev) => {
					const text = ev.target.value
					this.props.searchQuery.setQueryTerm(text)
				}
			},
		)
	}
}

class QueryPanel extends React.Component {
	constructor(props) {
		super(props)
	}

	getStyle() {
		return {
			width: "40%",
			height: "0.45in",
			padding: "0.1in",
			textAlign: "center",
			display: "block",
			margin: "auto",
		}
	}

	render() {
		const separate = percent => e('div', {
			style: {
				height: "100%",
				width: "3%",
				float: "left",
			},
		})
		return e(
			'div',
			{style: this.getStyle()},
			e(
				QueryBar,
				{
					color: this.props.color,
					searchQuery: this.props.searchQuery,
				}
			), separate(),
			e(
				SearchButton,
				{
					color: this.props.color,
					searchQuery: this.props.searchQuery,
					resultHandler: this.props.resultHandler,
					errorHandler: this.props.errorHandler,
					setPending: this.props.setPending,
				}
			), separate(),
			this.props.searchQuery.isFirstPage() ? null : e(
				PageJumper,
				{
					color: this.props.color,
					searchQuery: this.props.searchQuery,
					resultHandler: this.props.resultHandler,
					errorHandler: this.props.errorHandler,
					setPending: this.props.setPending,
					jump: -1, icon: "<<",
				}
			),
			this.props.searchQuery.isFirstPage() ? null : separate(),
			e(
				PageJumper,
				{
					color: this.props.color,
					searchQuery: this.props.searchQuery,
					resultHandler: this.props.resultHandler,
					errorHandler: this.props.errorHandler,
					setPending: this.props.setPending,
					jump: 1, icon: ">>",
				}
			),
		)
	}
}

class SearchPanel extends React.Component {
	constructor(props) {
		super(props)
		this.searchQuery = new SearchQuery()
	}

	getStyle() {
		const color = this.props.color
		return {
			WebkitBoxShadow: `0px 0px 15px ${color}`,
			boxShadow: `0px 0px 15px ${color}`,
			width: "100%",
			height: "1.5in",
			backgroundColor: colors.grey,
			textAlign: "center",
			borderBottom: `1px solid ${color}`,
		}
	}

	render() {
		const color = this.props.color
		return e(
			'div',
			{style: this.getStyle()},
			e(
				QueryPanel,
				{
					color: color,
					searchQuery: this.searchQuery,
					resultHandler: this.props.resultHandler,
					errorHandler: this.props.errorHandler,
					setPending: this.props.setPending,
				},
			),
			e(
				ConstraintPanel,
				{
					color: color,
					searchQuery: this.searchQuery,
				},
			),
		)
	}
}

/* TODO: Language */
/* TODO: Movie download page */
class MoviePortrait extends React.Component {
	constructor(props) {
		super(props)
		this.state = {
			mouseOver: false,
		}
	}

	getStyle() {
		const outset = this.state.mouseOver ? 15 : 0
		return {
			width: "80%",
			height: "70%",
			border: `2px solid white`,
			borderRadius: "3px",
			WebkitBoxShadow: `0 0 ${outset}px 0 ${colors.green}`,
			boxShadow: `0 0 ${outset}px 0 ${colors.green}`,
			cursor: "pointer",
		}
	}

	render() {
		return e(
			'img',
			{
				style: this.getStyle(),
				src: this.props.imageLink,
				onMouseOver: () => { this.setState({mouseOver: true}) },
				onMouseOut: () => { this.setState({mouseOver: false}) },
				onClick: this.props.onClick,
			},
		)
	}
}

class MovieTitle extends React.Component {
	constructor(props) {
		super(props)
	}

	getStyle() {
		return {
			width: "100%",
			height: "10%",
			textAlign: "center",
			whiteSpace: "nowrap",
			overflow: "hidden",
		}
	}

	render() {
		return e(
			'div',
			{style: this.getStyle()},
			e('font', {color: colors.white}, this.props.title),
		)
	}
}

class DownloadProgressBar extends React.Component {
	constructor(props) {
		super(props)
	}

	getStyle() {
		return {
			width: "100%",
			height: "10%",
			display: "block",
		}
	}

	renderDone() {
		const percentage = this.props.percentage
		const done = percentage == 100
		const barColor = done ? colors.green : colors.cyan
		const endRadii = done ? 5 : 0
		return e('div', {
			style: {
				backgroundColor: colors.black,
				borderRadius: `5px ${endRadii}px ${endRadii}px 5px`,
				width: `${percentage}%`,
				height: "100%",
				WebkitBoxShadow: `inset 0 0 20px 0 ${barColor}`,
				boxShadow: `inset 0 0 20px 0 ${barColor}`,
			},
		})
	}

	renderRemaining() {
		return e('div', {
			style: {
				backgroundColor: colors.black,
				borderRadius: `0 5px 5px 0`,
				width: `${100 - this.props.percentage}%`,
				height: "100%",
			},
		})
	}

	render() {
		return e(
			'div',
			{style: this.getStyle()},
			this.renderDone(),
		)
	}
}

class MovieItem extends React.Component {
	constructor(props) {
		super(props)
	}

	getStyle() {
		return {
			position: "relative",
			zIndex: 0,
			width: "12.5%",
			height: "45%",
		}
	}

	render() {
		const movieData = this.props.movieData
		/* TODO: GET info from transmission */
		const downloading = false
		const downloadProgress = 35
		return e(
			'div',
			{style: this.getStyle()},
			e(
				'div',
				{style: {padding: "5%", textAlign: "center"}},
				e(MoviePortrait, {
					imageLink: movieData.medium_cover_image,
					onClick: this.props.openMovie,
				}),
				e(MovieTitle, {
					title: movieData.title_long,
				}),
				downloading ? e(DownloadProgressBar, {
					percentage: downloadProgress,
				}) : null,
			),
		)
	}
}

class MovieList extends React.Component {
	constructor(props) {
		super(props)
	}

	getStyle() {
		return {
			width: "100%",
			height: "calc(100% - 1.5in - 0.34in)",
			display: "flex",
			flexWrap: "wrap",
			marginTop: "0.33in",
		}
	}

	renderList(ytsData) {
		const renderp = text => e(
			'p',
			{
				style: {
					position: "relative",
					zIndex: 0,
				},
			},
			e('font', {color: colors.white}, text),
		)
		if (!ytsData.movies)
			return ytsData.searched ? renderp("No movies found") : null
		return ytsData.movies.map(
			(m, i) => e(MovieItem, {
				key: i,
				movieData: m,
				openMovie: () => { this.props.movieOpener(m) },
			})
		)
	}

	render() {
		return e(
			'div',
			{style: this.getStyle()},
			this.renderList(this.props.ytsData)
		)
	}
}

class OverlayButton extends React.Component {
	constructor(props) {
		super(props)
		this.state = {
			mouseOver: false,
		}
	}

	getStyle() {
		const outset = this.state.mouseOver ? 15 : 5
		const color = this.props.color ? this.props.color : colors.white
		return {
			border: `1px solid ${color}`,
			borderRadius: "20%",
			WebkitBoxShadow: `0 0 ${outset}px 0 ${color}`,
			boxShadow: `0 0 ${outset}px 0 ${color}`,
			width: "0.6in",
			height: "0.25in",
			marginLeft: "5px",
			textAlign: "center",
			cursor: "pointer",
			paddingLeft: "5px",
			paddingRight: "5px",
		}
	}

	render() {
		const _3D_ = [e('font',{color:"#00FFFF"},'3'), e('font',{color:"#FF0000"},'D')]
		const text = this.props.text == "3D" ? _3D_ : this.props.text
		return e(
			'submit',
			{
				style: this.getStyle(),
				onMouseOver: () => { this.setState({mouseOver: true}) },
				onMouseOut: () => { this.setState({mouseOver: false}) },
				onClick: this.props.clickHandler
			},
			e('font', {color: colors.white}, text),
		)
	}
}

class OverlayDownloadProgress extends React.Component {
	constructor(props) {
		super(props)
	}

	getStyle() {
		return {
		}
	}

	render() {
		return e(
			'div',
			{style: this.getStyle()},
			/* TODO: Quality::Type, progress, pause/resume, cancel, delete */
		)
	}
}

class OverlayDownloadProgressBox extends React.Component {
	constructor(props) {
		super(props)
	}

	getStyle() {
		return {
		}
	}

	render() {
		return e(
			'div',
			{style: this.getStyle()},
		)
	}
}

class OverlayOptions extends React.Component {
	constructor(props) {
		super(props)
	}

	getStyle() {
		return {
			width: "100%",
			height: "50%",
			padding: "1in",
			position: "relative",
			display: "inline-block",
		}
	}

	renderText(text, fontSize, fontFamily) {
		return e('font', {
			style: {
				color: colors.white,
				marginRight: "0.1in",
				marginTop: "0.025in",
				fontSize: fontSize,
				family: fontFamily,
			},
		}, text)
	}

	renderDownloadOptions(movie) {
		return e(
			'div',
			{style: {
				width: "100%",
				height: "20%",
			}},
			this.renderText("Download: "),
			movie.torrents.map(
				torrent => e(OverlayButton, {
					text: torrent.quality,
					color: torrent.type == "bluray" ? colors.blue : null,
				})
			),
		)
	}

	renderTitle(movie) {
		return e(
			'div',
			{style: {
				width: "100%",
				height: "20%",
			}},
			this.renderText(movie.title_long, "xx-large"),
		)
	}

	renderGenres(movie) {
		const getGenreColor = genre => {
			if (genre == "Horror")
				return "#000060"
			else if (genre == "Mystery")
				return "#602060"
			else if (genre == "Sci-Fi")
				return "#FF0000"
			else if (genre == "Drama")
				return "#FF20AF"
			else if (genre == "Fantasy")
				return "#D08090"
			else if (genre == "Action")
				return "#FF7F00"
			else if (genre == "Adventure")
				return "#000FFF"
			else if (genre == "Thriller")
				return "#600000"
			else
				return "#FFFFFF"
		}
		return e(
			'div',
			{style: {
				width: "100%",
				height: "20%",
			}},
			// this.renderText("Genres: "),
			movie.genres.map(
				genre => e(OverlayButton, {
					text: genre,
					color: getGenreColor(genre),
				})
			)
		)
	}

	renderRating(movie) {
		return e(
			'div',
			{style: {
				width: "100%",
				height: "20%",
			}},
			this.renderText("IMDB rating: " + movie.rating + "/10")
		)
	}

	renderSynopsis(movie) {
		return e(
			'div',
			{style: {
				width: "100%",
				height: "20%",
			}},
			this.renderText("SYNOPSIS: " + movie.synopsis)
		)
	}

	render() {
		const movie = this.props.movie
		return e(
			'div',
			{style: this.getStyle()},
			this.renderTitle(movie),
			this.renderGenres(movie),
			this.renderRating(movie),
			this.renderDownloadOptions(movie),
			this.renderSynopsis(movie),
		)
	}
}

class MovieOverlay extends React.Component {
	constructor(props) {
		super(props)
	}

	getStyle() {
		return {
			position: "fixed",
			display: "block",
			width: "100%",
			height: "100%",
			top: 0,
			left: 0,
			right: 0,
			bottom: 0,
			backgroundColor: `rgba(0, 0, 0, 0.8)`,
			display: "flex",
		}
	}

	render() {
		const imgLink = this.props.movie.large_cover_image
		const outset = 15
		return e(
			'div',
			{style: this.getStyle()},
			e(
				'div',
				{style: {height: "100%"}},
				e('img', {
					style: {
						height: "100%",
						WebkitBoxShadow: `0 0 ${outset}px 0 ${colors.white}`,
						boxShadow: `0 0 ${outset}px 0 ${colors.white}`,
					},
					src: imgLink,
				}),
			),
			e(OverlayOptions, {
				movie: this.props.movie,
			}),
			e(OverlayButton, {
				text: "Back",
				clickHandler: this.props.closer,
			}),
		)
	}
}

class MainPage extends React.Component {
	constructor(props) {
		super(props)
		this.state = {
			connStatus: "Undecided",
			ytsData: {
				err: "",
				searched: false,
				movies: [],
				movieOpen: null,
			},
		}
		this.searchResultHandler = this.searchResultHandler.bind(this)
		this.searchErrorHandler = this.searchErrorHandler.bind(this)
		this.setNetworkStatePending = this.setNetworkStatePending.bind(this)
		this.openMovie = this.openMovie.bind(this)
		this.closeMovie = this.closeMovie.bind(this)
	}

	getConnectivityColor(s) {
		if (s == "Connected")
			return colors.green
		else if (s == "Disconnected")
			return colors.red
		else if (s == "Undecided")
			return colors.yellow
		else
			return colors.magenta
	}

	searchResultHandler(movieList) {
		this.setState({
			connStatus: "Connected",
			ytsData: {
				err: "",
				searched: true,
				movies: movieList,
			},
		})
	}

	searchErrorHandler(err) {
		this.setState({
			connStatus: "Disconnected",
			ytsData: {
				err: err,
				searched: true,
				movies: [],
			},
		})
	}

	setNetworkStatePending() {
		this.setState({
			connStatus: "Undecided",
		})
	}

	openMovie(movie) {
		this.setState({
			movieOpen: movie,
		})
	}

	closeMovie() {
		this.setState({
			movieOpen: null,
		})
	}

	render() {
		const color = this.getConnectivityColor(this.state.connStatus)
		const blurFactor = this.state.movieOpen ? 13 : 0;
		return [
			e(
				'div',
				{
					style: {
						width: "100%",
						height: "100%",
						WebkitFilter: `blur(${blurFactor}px)`,
						MozFilter: `blur(${blurFactor}px)`,
						OFilter: `blur(${blurFactor}px)`,
						filter: `blur(${blurFactor}px)`,
					},
					key: 0,
				},
				e(SearchPanel, {
					color: color,
					resultHandler: this.searchResultHandler,
					errorHandler: this.searchErrorHandler,
					setPending: this.setNetworkStatePending,
				}),
				e(MovieList, {
					ytsData: this.state.ytsData,
					movieOpener: this.openMovie,
				}),
			),
			this.state.movieOpen ? e(MovieOverlay, {
				movie: this.state.movieOpen,
				closer: this.closeMovie,
				key: 1,
			}) : null,
		]
	}
}

ReactDOM.render(e(MainPage), document.getElementById('root'))
