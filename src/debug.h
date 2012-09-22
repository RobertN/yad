#ifdef DEBUG
# define debug(fmt, ...) \
	fprintf(stderr, "%s: " fmt "\n", __func__, ## __VA_ARGS__);
#else
# define debug(fmt, ...) 0;
#endif // DEBUG
