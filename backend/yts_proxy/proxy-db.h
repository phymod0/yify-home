#ifndef PROXY_DB
#define PROXY_DB


#include "../utils/trie.h"


/**
 * Status code for a database operation.
 */
typedef enum {
	FOUND,
	NOT_FOUND,
	SUCCESS,
	FAILURE_FILE_IO,
	FAILURE_NETWORK_IO,
	FAILURE_ALLOC,
	FAILURE_UNKNOWN,
} db_status_t;

/** Get the string representation of a status code.
 *
 * @param status The operation status code
 * @returns String representation of <code>status</code>.
 */
const char* db_status_str(db_status_t status);

/** Get a status code from its string representation.
 *
 * @param status String representation of the operation status code
 * @returns Status code.
 * @see <code>db_status_t</code> for all status codes.
 */
db_status_t db_status_code(const char* status);


/**
 * Main database context.
 *
 * Uses a trie of titles for optimizing search suggestions.
 */
typedef struct {
	trie_t* title_trie;
	FILE* db_fd;
	char* db_fp;
} db_ctx_t;

/** Load the database from a file.
 *
 * <code>*db_ctx</code> will point to a newly allocated database context which
 * must be freed explicitly via <code>db_destroy()</code>. The original context
 * pointer will be overwritten and must also be freed before calling
 * <code>db_load()</code> if necessary.
 *
 * Files that do not exist as described by <code>db_fp</code> will be created.
 *
 * @param db_ctx Pointer to database context pointer to overwrite
 * @param db_fp Database file path
 * @returns Status code.
 * @see db_status_t for all status codes.
 */
db_status_t db_load(db_ctx_t** const db_ctx, const char* db_fp);

/** Deallocate the database context.
 *
 * Frees all entries associated with the database.
 *
 * @param db_ctx Database context created with <code>db_load()</code>
 */
void db_destroy(db_ctx_t* db_ctx);


/**
 * Supported genre types.
 */
typedef enum {
	/* TODO: Continue specifying */
	HORROR, MYSTERY, ROMANCE, COMEDY, ACTION, THRILLER, UNKNOWN,
} db_genre_t;

/** Get the string representation of a genre type.
 *
 * @param genre The genre code
 * @returns Constant pointer to string representation or <code>NULL</code> if
 * unsupported genre code.
 */
const char* db_genre_str(db_genre_t genre);

/** Get a genre code from its string representation.
 *
 * @param genre String representation of the genre code
 * @returns Genre code or <code>UNKNOWN</code> if unsupported string.
 */
db_genre_t db_genre_code(const char* genre);


/**
 * Structure of a single database entry.
 *
 * <code>genre_list</code> contains all suggested genres for the movie.
 */
typedef struct db_entry_t {
	char *id, *title, *summary;
	genre_t* genre_list;
	unsigned rating, year;
} db_entry_t;

/** Allocate and initialize a database entry.
 *
 * It is expected that all created <code>db_entry_t</code>s are added to the
 * database with <code>db_add_entry()</code>. Entries are only deallocated by
 * calling <code>db_delete_entry()</code> on the database. No explicit
 * destructor is provided.
 *
 * @param id The YIFY id of the movie
 * @param title The movie title
 * @param summary The movie summary
 * @param genre_list All suggested genres of the movie
 * @param rating IMDB rating scaled from 0 to 100
 * @param year Year of release
 * @returns Pointer to allocated entry or <code>NULL</code> if the allocation
 * failed.
 */
db_entry_t* db_create_entry(const char* id, const char* title,
			    const char* summary, const genre_t* genre_list,
			    unsigned rating, unsigned year);

/** Add an entry to the database.
 *
 * <code>entry</code> is inserted into the database by reference without being
 * duplicated.
 *
 * @param db_ctx Database context
 * @param entry Entry to add
 *
 * @returns Status code.
 * @see <code>db_status_t</code> for all status codes.
 */
db_status_t db_add_entry(db_ctx_t* db_ctx, const db_entry_t* const entry);

/** Delete an entry from the database.
 *
 * Points <code>entry</code> to <code>NULL</code> if the deletion was
 * successful.
 *
 * @param db_ctx Database context
 * @param entry Entry in the database to delete
 */
void db_delete_entry(db_ctx_t* db_ctx, db_entry_t** const entry);


/**
 * Structure of a search preference.
 *
 * Movies with any genre contained in <code>genre_list</code> are considered.
 * Movies with any genre contained in <code>genre_blacklist</code> are not.
 * Movies with any genre contained in both are not.
 */
typedef struct {
	char* title_prefix;
	genre_t *genre_list, *genre_blacklist;
	unsigned min_rating, max_rating, min_year, max_year;
} db_pref_t;

/** Define and instantiate a search preference.
 *
 * <code>title_prefix</code>, <code>genre_list</code> and
 * <code>genre_blacklist</code> are deep-copied and must be <code>free</code>d
 * explicitly.
 *
 * Returned preference structure must be freed explicitly via
 * <code>db_pref_destroy()</code>.
 *
 * @param title_prefix NULL, or prefixes all titles of movies to select
 * @param genre_list NULL, or coincides with all genres of movies to select
 * @param genre_blacklist NULL, or disjoint from all genres of movies to select
 * @param min_rating <= the rating of any movie to select
 * @param max_rating UINT_MAX, or >= the rating of any movie to select
 * @param min_year <= the release year of any movie to select
 * @param max_year UINT_MAX, or >= the release year of any movie to select
 * @returns Pointer to instantiated preference.
 */
db_pref_t* db_pref_create(const char* title_prefix, const genre_t* genre_list,
			  const genre_t* genre_blacklist, unsigned min_rating,
			  unsigned max_rating, unsigned min_year,
			  unsigned max_year);

/** Deallocate a preference object.
 *
 * @param pref Preference object to destroy
 */
void db_pref_destroy(db_pref_t* pref);


/**
 * Result of a database query.
 *
 * Database entries are loaded into <code>entries</code> by reference.
 */
typedef struct {
	size_t n_entries;
	db_entry_t** entries;
} db_result_t;

/** Retrieve a query result containing entries satisyfing <code>pref</code>.
 *
 * Returned result structure must be freed explicitly via
 * <code>db_result_destroy()</code>.
 *
 * @param db_ctx Database context
 * @param pref Pointer to preference structure
 * @returns Pointer to query result structure.
 */
db_result_t* db_query(const db_ctx* db_ctx, const db_pref_t* pref);

/** Deallocate a result object.
 *
 * @param result Result object to deallocate
 */
void db_result_destroy(db_result_t* result);


/**
 * Types of orders on <code>db_entry_t</code>.
 */
typedef enum {
	ORD_RATING,
	ORD_YEAR,
	ORD_TITLE,
} db_ordtype_t;

/**
 * Instantiation of a <code>db_entry_t</code> order.
 *
 * <code>weight</code>: <0 if descending, 0 if irrelevant, >0 if ascending.
 */
typedef struct {
	db_ordtype_t ordtype;
	int weight;
} db_order_t;

/** Sort query result using an array of <code>db_entry_t</code> orders.
 *
 * Orders occuring earlier in the list are given a higher preference.
 *
 * @param result Query result from <code>db_query()</code>
 * @param orders Array of <code>db_entry_t</code> orders
 */
void db_sort_results(db_result_t* result, const db_order_t* orders);


#endif /* PROXY_DB */
