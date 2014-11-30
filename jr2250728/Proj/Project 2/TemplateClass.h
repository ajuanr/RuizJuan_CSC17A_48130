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
    Game(const T&);
    T& operator=(const T&);
    T* operator->();
    T operator*();
};

#endif /* defined(__Project_2__TemplateClass__) */
