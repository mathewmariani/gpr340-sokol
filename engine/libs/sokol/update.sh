#!/bin/bash
# update the required sokol headers

# repo url
SOKOL_PREFIX="https://raw.githubusercontent.com/floooh/sokol/master"

# headers
SOKOL_APP="$SOKOL_PREFIX/sokol_app.h"
SOKOL_ARGS="$SOKOL_PREFIX/sokol_args.h"
SOKOL_AUDIO="$SOKOL_PREFIX/sokol_audio.h"
SOKOL_GFX="$SOKOL_PREFIX/sokol_gfx.h"
SOKOL_GLUE="$SOKOL_PREFIX/sokol_glue.h"
SOKOL_LOG="$SOKOL_PREFIX/sokol_log.h"

# utils
SOKOL_GL="$SOKOL_PREFIX/util/sokol_gl.h"
SOKOL_IMGUI="$SOKOL_PREFIX/util/sokol_imgui.h"

# output directory
OUTPUT=./engine/libs/sokol

# curl all headers and utils
curl $SOKOL_APP > $OUTPUT/sokol_app.h
curl $SOKOL_ARGS > $OUTPUT/sokol_args.h
curl $SOKOL_ARGS > $OUTPUT/sokol_audio.h
curl $SOKOL_GFX > $OUTPUT/sokol_gfx.h
curl $SOKOL_GLUE > $OUTPUT/sokol_glue.h
curl $SOKOL_LOG > $OUTPUT/sokol_log.h

# utils
curl $SOKOL_GL > $OUTPUT/sokol_gl.h
curl $SOKOL_IMGUI > $OUTPUT/sokol_imgui.h
