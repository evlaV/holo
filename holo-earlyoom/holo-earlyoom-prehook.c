/*
 * SPDX-License-Identifier: MIT
 *
 * Copyright 2025 © Valve Corporation.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the “Software”), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define FILENAME_SIZE 256
#define BUFFER_SIZE 4096
const char *expected_varname = "SteamAppId";

struct Buffer_t {
  char data[BUFFER_SIZE];
  size_t index;
};
typedef struct Buffer_t Buffer;


// write given string to given file
//
// returns EXIT_SUCCESS / EXIT_FAILURE
int write_string_to_file(const char *str, const char *file_path) {
	FILE *file = fopen(file_path, "w");
	if (!file) {
		fprintf(stderr, "error: opening output file '%s' for writing: %s\n", file_path, strerror(errno));
		return EXIT_FAILURE;
	}

	fprintf(file, str);
	fprintf(file, "\n");
	fclose(file);

	return EXIT_SUCCESS;
}

// compare var name, the left side of '=' in "VAR=value"
//
// returns EXIT_SUCCESS / EXIT_FAILURE
int var_name_matches(Buffer *buffer, const char *varname) {
	// buffer should at least be varname_len +2 because of needing to take
	// '=' sign into account (necessary because of the comparison later) and
	// also be null-terminated
	const size_t varname_len = strlen(varname);
	if (BUFFER_SIZE < (varname_len + 2)) {
		return EXIT_FAILURE;
	}

	// compare each character in the same position, bail out early if they
	// do not match
	for (size_t i = 0; i < varname_len; ++i) {
		if (buffer->data[i] != varname[i]) {
			return EXIT_FAILURE;
		}
	}

	// check that the next character in the buffer after varname is '=', to
	// match exactly and not just partially
	if (varname_len >= BUFFER_SIZE || buffer->data[varname_len] != '=') {
		return EXIT_FAILURE;
	}

	// seems OK
	return EXIT_SUCCESS;
}

void usage(const char *program_name) {
	fprintf(stderr,	"Usage: %s\n", program_name);
}

int main(int argc, char *argv[]) {

	// arg check
	if (argc != 1) {
		fprintf(stderr, "error: does not accept arguments, %i given: ", argc);
		for (int i = 0; i < argc; ++i) {
			fprintf(stderr, "'%s' ", argv[i]);
		}
		fprintf(stderr, "\n");

		usage(argv[0]);
		return EXIT_FAILURE;
	}

	// derive files from environment variables, (E)UID
	const char *env_EARLYOOM_PID = getenv("EARLYOOM_PID");
	if (!env_EARLYOOM_PID) {
		fprintf(stderr, "error: missing variable 'EARLYOOM_PID' for reading\n");
		return EXIT_FAILURE;
	}
	char input_file[FILENAME_SIZE]  = { 0 };
	char output_file[FILENAME_SIZE] = { 0 };
	snprintf(input_file,  sizeof(input_file),  "/proc/%s/environ", env_EARLYOOM_PID);
	snprintf(output_file, sizeof(output_file), "/run/holo-earlyoom/prehook-report-%s", env_EARLYOOM_PID);

	// open the input file in binary mode
	FILE *file = fopen(input_file, "rb");
	if (!file) {
		fprintf(stderr, "error: opening input file '%s' for reading: %s\n", input_file, strerror(errno));
		return EXIT_FAILURE;
	}

	// read vars and extract SteamAppId if available
	int ret_code = EXIT_FAILURE;
	while (1) {
		Buffer buffer = { .data = {'\0'}, .index = 0 }; // reset in each iteration
		int c = 0;

		// get one var into the buffer
		do {
			c = fgetc(file);

			// fill buffer, one char at a time, with proper checks
			//
			// even if buffer full we pretend that it doesn't matter
			// (if the varname was larger than BUFFER_SIZE, unlikely
			// in the real world, it will not match later, so it is
			// not critical to admit absurdly large var names)
			if (c == '\0' || c == EOF) {
				// fprintf(stderr, "DBG: reached end of var ('\\0') or EOF, buffer terminated with zero\n");
				buffer.data[buffer.index++] = '\0';
			}
			else if (buffer.index < (BUFFER_SIZE - 1)) {
				// fprintf(stderr, "DBG: adding '%c' (%x)\n", c, c);
				buffer.data[buffer.index++] = c;
			}
			else {
				// see comment on header, not important
				// fprintf(stderr, "warning: buffer full, will not admit new character '%c'\n", c);
				buffer.data[BUFFER_SIZE-1] = '\0';
			}
		}
		while (c != '\0' && c != EOF);

		// see if we read the desired var, if so, job done
		if (var_name_matches(&buffer, expected_varname) == EXIT_SUCCESS) {
			// fprintf(stderr, "DBG: matches!! '%s'\n", buffer.data);
			int res_write = write_string_to_file(buffer.data, output_file);
			ret_code = res_write;
			break;
		}
		else {
			// fprintf(stderr, "DBG: does NOT match!!!!!! '%s'\n", buffer.data);
		}

		// if EOF, stop
		if (c == EOF) {
			fprintf(stderr, "error: reached EOF without finding expected variable '%s', stopping\n", expected_varname);
			ret_code = EXIT_FAILURE;
			break;
		}
	}

	fclose(file);

	return ret_code;
}
