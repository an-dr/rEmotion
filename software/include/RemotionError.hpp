// *************************************************************************
//
// Copyright (c) 2024 Andrei Gramakov. All rights reserved.
//
// site:    https://agramakov.me
// e-mail:  mail@agramakov.me
//
// *************************************************************************

#pragma once

enum class RemotionError {
    NO_ERROR,
    ERROR,
    ERROR_OPEN_PORT,
    ERROR_READ_PORT,
    ERROR_WRITE_PORT,
    ERROR_CLOSE_PORT,
    ERROR_READ_IMAGE,
    ERROR_START
};
