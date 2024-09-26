// *************************************************************************
//
// Copyright (c) 2024 Andrei Gramakov. All rights reserved.
//
// site:    https://agramakov.me
// e-mail:  mail@agramakov.me
//
// *************************************************************************

#pragma once

#include "RemotionError.hpp"
#include "RemotionExpression.hpp"

struct RemotionStatus {
    RemotionError cameraError;
    RemotionError displayError;
    RemotionExpression displayExpression;
};
