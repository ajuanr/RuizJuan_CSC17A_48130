//
//  TemplateClass.h
//  Project 2
//
//  Created by Juan on 11/29/14.
//  Copyright (c) 2014 Juan Ruiz. All rights reserved.
//

#ifndef __Project_2__TemplateClass__
#define __Project_2__TemplateClass__

template<class T>
class AnyGame {
private:
    T* p;
public:
    AnyGame():p(0){}
    AnyGame(T* t):p(t){}
    ~AnyGame() {delete p;}
    AnyGame<T>& operator=(const T&);
    operator bool(){return p;}
    T* operator->() const;
    T& operator*() const;
};

template<class T>
T* AnyGame<T>::operator->() const {
    /// only return p if it points to something
    if (p)
        return p;
}

template<class T>
T& AnyGame<T>::operator*() const{
    if (p)
        return *p;
}

template<class T>
AnyGame<T>& AnyGame<T>::operator=(const T& rhs) {
    p = &rhs;
}

#endif /* defined(__Project_2__TemplateClass__) */
