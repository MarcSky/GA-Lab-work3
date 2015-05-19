//
//  main.cpp
//  laba3
//
//  Created by Levan Gogohia on 12.05.15.
//  Copyright (c) 2015 Levan Gogohia. All rights reserved.
//

#include <iostream>
#include <stdlib.h>
#define CHROMOSOME_SIZE 8
#define MUTATION_RATE 10

struct chromosome{
    chromosome(){
        for(int i = 0; i < CHROMOSOME_SIZE; i++) {
            genes[i] = rand()%255;
        }
    }
    void print(){
        for(int i = 0; i < CHROMOSOME_SIZE; i++) {
            std::cout<< genes[i] << " ";
        }
        std::cout << std::endl;
    }
    int genes[CHROMOSOME_SIZE];
};


void simple_single_point_mutation(chromosome * a) {
    std::cout << "Однототечная мутация" << std::endl;
    int point = rand() % CHROMOSOME_SIZE;
    a->print();
    std::cout<< point <<std::endl;
    
    if(point + 1 < CHROMOSOME_SIZE) {
        std::swap(a->genes[point], a->genes[point+1]);
    }
    a->print();
}

void simple_two_point_mutation(chromosome * a) {
    std::cout << "Двухточечная мутация" << std::endl;

    int one_point = rand() % CHROMOSOME_SIZE;
    int two_point = 0;
    
    while(one_point == two_point) {
        two_point = rand() % CHROMOSOME_SIZE;
    }
    
    a->print();
    std::cout<< one_point <<std::endl;
    std::cout<< two_point <<std::endl;
    
    std::swap(a->genes[one_point],a->genes[two_point]);
    a->print();
}

void reverse(int * desc, int * source, int point) {
    for(int i = CHROMOSOME_SIZE - 1; i >= point; i--) {
        desc[(CHROMOSOME_SIZE - 1) - i] = source[i];
    }
}

void inversion_one_mutation(chromosome * a) {
    
    std::cout << "Инверсия" << std::endl;

    int point = rand() % CHROMOSOME_SIZE;
    int local_genes[CHROMOSOME_SIZE];
    memset(local_genes, -1, sizeof(int) * CHROMOSOME_SIZE);

    a->print();
    std::cout<< point <<std::endl;

    reverse(local_genes, a->genes, point);
    
    memcpy(&a->genes[point], &local_genes, sizeof(int) * (CHROMOSOME_SIZE-point));
    a->print();
}


void translocation_mutation(chromosome * a, chromosome * b) {
    std::cout << "Транслокация" << std::endl;

    int point = rand() % CHROMOSOME_SIZE;
    
    std::cout<< point <<std::endl;
    a->print();
    b->print();
    
    chromosome temp;
    memcpy(temp.genes, a->genes, sizeof(int) * CHROMOSOME_SIZE);
    
    int local_genes[CHROMOSOME_SIZE];
    reverse(local_genes, b->genes, point);
    
    memcpy(&a->genes[point], local_genes, sizeof(int) * (CHROMOSOME_SIZE - point));;
    
    reverse(local_genes, temp.genes, point);
    memcpy(&b->genes[point], local_genes, sizeof(int) * (CHROMOSOME_SIZE - point));;

    
    a->print();
    b->print();
}

void gold_mutation(chromosome * a) {
    std::cout << "Золотое сечение" << std::endl;

    double size = CHROMOSOME_SIZE;
    size /= 1.6180339;
    int point = (rand() % 2) ? CHROMOSOME_SIZE - size - 1 : 0 + (int)size;
    std::cout << point << std::endl;
    a->print();
    
    if(point < CHROMOSOME_SIZE / 2) {
        for(int i=0,j=point+1;i<point;i++,j++){
            std::swap(a->genes[i],a->genes[j]);
        }
    }
    
    if(point > CHROMOSOME_SIZE / 2) {
        for(int i=CHROMOSOME_SIZE-1,j=point-1;i>point;i--,j--){
            std::swap(a->genes[i],a->genes[j]);
        }
    }
    a->print();

}

void fibonaci_mutation(chromosome * a) {
    
    int fibonaci[CHROMOSOME_SIZE - 2] = {0,1,1,2,3,5};
    int temp = 0;
    a->print();

    do{
        temp = rand() % CHROMOSOME_SIZE - 2;
    }while( !temp );
    
    std::cout << temp << std::endl;
    std::swap(a->genes[fibonaci[temp]], a->genes[fibonaci[temp-1]]);
    
    a->print();
}

int main(int argc, const char * argv[]) {
    srand((unsigned)time(NULL));
    chromosome t1;
    chromosome t2;
    gold_mutation(&t1);
    return 0;
}