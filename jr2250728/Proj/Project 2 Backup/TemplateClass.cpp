//
//  TemplateClass.cpp
//  Project 2
//
//  Created by Juan on 11/29/14.
//  Copyright (c) 2014 Juan Ruiz. All rights reserved.
//

#include "TemplateClass.h"

//template<class T>
//Game<T>::Game(T* rhs) {
//    p = rhs;
//}

template<class T>
T* Game<T>::operator->() const {
    /// only return p if it points to something
    if (p)
        return p;
}

template<class T>
T& Game<T>::operator*() const{
    if (p)
        return *p;
}

template<class T>
Game<T>& Game<T>::operator=(const T& rhs) {
    p = &rhs;
    return *this;
}
