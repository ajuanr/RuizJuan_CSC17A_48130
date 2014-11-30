//
//  TemplateClass.cpp
//  Project 2
//
//  Created by Juan on 11/29/14.
//  Copyright (c) 2014 Juan Ruiz. All rights reserved.
//

#include "TemplateClass.h"

template<class T>
Game<T>::Game(const T& rhs) {
    p = &rhs;
}

template<class T>
T* Game<T>::operator->() {
    /// only return p if it points to something
    if (p)
        return p;
}

template<class T>
T Game<T>::operator*() {
    if (p)
        return *p;
}

template<class T>
T& Game<T>::operator=(const T& rhs) {
    p = &rhs;
    return *this;
}
