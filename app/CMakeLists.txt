#-------------------------------------------------------------------------------
# Zephyr Example Application
#
# Copyright (c) 2021 Nordic Semiconductor ASA
# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.13.1)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

project(app LANGUAGES C)

zephyr_include_directories(src)

target_sources(app PRIVATE src/main.c)

target_sources(app PRIVATE src/UploadtoScreen.c)

#Runes
target_sources(app PRIVATE src/BlueRune.c)
target_sources(app PRIVATE src/GreenRune.c)
target_sources(app PRIVATE src/PurpleRune.c)
target_sources(app PRIVATE src/RedRune.c)

#Hearts
target_sources(app PRIVATE src/HeartRune.c)
target_sources(app PRIVATE src/GreyHeartRune.c)
target_sources(app PRIVATE src/ThreeHeartsRune.c)
target_sources(app PRIVATE src/TwoHeartsRune.c)
target_sources(app PRIVATE src/OneHeartRune.c)
target_sources(app PRIVATE src/ZeroHeartRune.c)

#Title
target_sources(app PRIVATE src/RuneTitle.c)

target_sources(app PRIVATE src/game_sm.c)