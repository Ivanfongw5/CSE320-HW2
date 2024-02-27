#include <stdio.h>
#include <stdlib.h>

#include "const.h"
#include "debug.h"
#include "audio.h"

#ifdef _STRING_H
#error "Do not #include <string.h>. You will get a ZERO."
#endif

#ifdef _STRINGS_H
#error "Do not #include <strings.h>. You will get a ZERO."
#endif

#ifdef _CTYPE_H
#error "Do not #include <ctype.h>. You will get a ZERO."
#endif


#define nelem(arr) (sizeof(arr) / sizeof(arr[0]))


// struct _test_context {
// 	int duration;
// 	size_t expected_output_len;
// 	size_t input_buf_len;
// 	size_t input_actual_len;
// 	size_t nsamples;
// 	char *input;
// 	char *output;
// 	FILE *fin;
// 	FILE *fout;
// };

// struct _dtmf_event {
// 	uint32_t start_index;
// 	uint32_t end_index;
// 	uint8_t symbol;
// };

// int dtmf_event_to_text(struct _dtmf_event *_events, int n, char *text)
// {
// 	char *textptr = text;
// 	int linelen, total_len = 0;
// 	/* {UINT32_MAX}\t{UINT32_MAX}\t{CHAR}\n */
// 	const int line_max_size = 10 + 1 + 10 + 1 + 1 + 1;
// 	for (int i = 0; i < n; ++i) {
// 		linelen = snprintf(textptr, line_max_size, "%u\t%u\t%c\n",
// 				   _events[i].start_index, _events[i].end_index,
// 				   _events[i].symbol);
// 		textptr += linelen;
// 		total_len += linelen;
// 	}
// 	*textptr = '\0';
// 	return total_len;
// }


// static void setup_test(struct _test_context *ctx, struct _dtmf_event *events,
// 		       int n, int duration, int input_buf_len)
// {
// 	/* Assign context values */
// 	ctx->duration = duration;
// 	ctx->expected_output_len =
// 	    sizeof(AUDIO_HEADER) +
// 	    duration * AUDIO_FRAME_RATE / 1000 * sizeof(int16_t);
// 	ctx->input_buf_len = input_buf_len;
// 	ctx->input_actual_len = 0;
// 	ctx->nsamples = duration * AUDIO_FRAME_RATE / 1000;

// 	/* Allocate input and output buffer */
// 	ctx->input = malloc(input_buf_len);
// 	ctx->output = malloc(ctx->expected_output_len + 1);

// 	/* Generate dtmf event input text */
// 	ctx->input_actual_len = dtmf_event_to_text(events, n, ctx->input);

// 	/* Open files */
// 	ctx->fin = fmemopen(ctx->input, ctx->input_actual_len, "r");

// 	ctx->fout = fmemopen(ctx->output, ctx->expected_output_len + 1, "wb");
// }

// static void cleanup_test(struct _test_context *ctx)
// {
// 	fclose(ctx->fin);
// 	fclose(ctx->fout);
// 	free(ctx->input);
// 	free(ctx->output);
// }

AUDIO_HEADER header;
int main(int argc, char **argv)
{
    if(validargs(argc, argv))
        USAGE(*argv, EXIT_FAILURE);
    else
        USAGE(*argv, EXIT_SUCCESS);

    // FILE * f = fopen("/home/student/Desktop/snahian/hw1/all941.au", "r");
    // audio_read_header(f, &header);

    int generate_command_used = (global_options & 2) >> 1;
    if (generate_command_used) {
        // -g flag was used
        if (dtmf_generate(stdin, stdout, audio_samples) == EOF) {
            return EXIT_FAILURE;
        }
        return EXIT_SUCCESS;
    }
    int detect_command_used = (global_options & 4) >> 2;
    if (detect_command_used) {
        // the -d flag was used
            // printf("WHAT\n");
        if (dtmf_detect(stdin, stdout) == EOF) {
            return EXIT_FAILURE;
        }
        return EXIT_SUCCESS;
    }

    // means that another command was used (should never reach this point because of the validation done at validate args)
    return EXIT_FAILURE;

    // struct _dtmf_event events[] = {{100, 500, '5'},
	// 			       {1500, 2000, '6'},
	// 			       {3000, 5000, '7'},
	// 			       {6000, 7000, 'A'},
	// 			       {7200, 8800, '#'}};

	// struct _test_context ctx;
	// setup_test(&ctx, events, nelem(events), 950, 4096);

	// int ret = dtmf_generate(ctx.fin, ctx.fout, ctx.nsamples);

	// cleanup_test(&ctx);
}

/*
 * Just a reminder: All non-main functions should
 * be in another file not named main.c
 */

