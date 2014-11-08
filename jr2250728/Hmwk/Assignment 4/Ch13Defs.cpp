//
//  Ch13Defs.cpp
//  RuizJuan-Chapter13
//
//  Created by Juan Ruiz on 11/7/14.
//  Copyright (c) 2014 Juan Ruiz. All rights reserved.
//

#include <stdio.h>
#include "Ch13Prototypes.h"

Date::Date(int m, int d, int y) {
    (m < 13 && m > 0) ? month = m: month=1;
    (d < 32 && d > 0) ? day = d: day=1;
    (y < 2050 && y > 1950 ) ? year = d: year=1950;
}