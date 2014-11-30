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
class Game {
private:
    T* p;
public:
    Game():p(0){}
    Game(T* t):p(t){}
    ~Game() {delete p;}
    Game<T>& operator=(const T&);
    operator bool(){return p;}
    T* operator->() const;
    T& operator*() const;
};

#endif /* defined(__Project_2__TemplateClass__) */
