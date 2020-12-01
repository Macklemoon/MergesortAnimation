#include <QApplication>
#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsLineItem>
#include <QColor>
#include <vector>
#include <unistd.h>
#include <sstream>
#include <iostream>
#include <stdlib.h>
#include <algorithm>
#define WHITE QColor(255, 255, 255)
#define GREEN QColor(55, 200, 0)
#define BLUE QColor(11, 97, 164)
#define RED QColor(255, 57, 0)
#define ORANGE QColor(255, 191, 0)
#define APPLE QColor(165, 255, 0)
#define PURPLE QColor(124, 7, 169)

#include "utils.h"

class mergesort {
public:
    // Overload for public use. Recursion procs in private helper.
    void sort() {
      int* aux = new int [size];
      assert(aux != nullptr);
      sort(aux, 0, size - 1);

      for(size_t i = 0; i < size; ++i) {
          solved(i);
      }
    }
    mergesort(QGraphicsScene *scene, int *array) : mergesort(scene, array, 256, 10000) {}

    mergesort(QGraphicsScene *scene, int *array, size_t sizeGiven, int delay) {
        arr = array;
        // Randomize array(?)
        size = sizeGiven;
        m_scene = scene;
        m_delay = delay;
        m_width = (512/size < 1) ? 1 : 512/size;

        for(size_t i = 0; i < size; ++i) {
            int height = (arr[i] + 1) * m_width;
            float left = 10 + i * m_width;
            int intLeft = left * 1;

            if(left - intLeft < 0.1) {
                left = intLeft;
            } else if(left - intLeft < 0.6) {
                left = intLeft + 0.5;
            } else {
                left = intLeft + 1;
            }

            int up = 540 - height;
            QPen pen = QPen(Qt::black);
            QBrush brush = QBrush(ORANGE);
            m_rects.push_back(m_scene->addRect(left, up, m_width, height, pen, brush));
        }
    }

    void updateArr(int* array) {
        arr = array;
        for(size_t i = 0; i < size; ++i) {
            render(i, ORANGE);
        }
    }
private:
    int* arr;
    QGraphicsScene* m_scene;
    size_t size;
    std::vector<QGraphicsRectItem *> m_rects;
    int m_delay;

    int m_width;

    void delay() {
        for(int i = 0; i <= m_delay/6; ++i) {
            QApplication::processEvents();
        }
    }

    void solved(size_t i) {
        render(i, GREEN);
        QApplication::processEvents();
    }

    void tmpSolve(size_t i) {
        render(i, APPLE);
        QApplication::processEvents();
    }

    void render(size_t i, QColor c) {
        int height = (arr[i] + 1) * m_width;
        int left = 10 + i * m_width;
        int up = 540 - height;

        QPen pen = QPen(Qt::black);
        QBrush brush = QBrush(c);
        m_rects[i]->setBrush(brush);
        m_rects[i]->setPen(pen);
        m_rects[i]->setRect(QRect(left, up, m_width, height));
    }

    // Var indicates how large arrays will be at the base case.
    static const int CUTOFF = 7;

    // Recursive method that sorts both sides separately, and merges the two mostly sorted arrays.
    void sort(int* aux, size_t low, size_t high) {
      // if the size of the array is at a certain point,
      // sort before more cracking, then return.
      if(high <= low) {
          return;
      }

      // gets middle of current array's size.
      size_t mid = low + ((high - low) / 2);

      // Sort from lower end of currently spectating chunk.
      sort(aux, low, mid);
      for(size_t i = low; i <= mid; ++i) {
          tmpSolve(i);
      }
      // Sort the higher portion of the array.
      sort(aux, mid + 1, high);
      for(size_t i = mid + 1; i <= high; ++i) {
          tmpSolve(i);
      }
      merge(aux, low, mid, high);
    }

    // Nitty gritty pretty details. Iterates through the two, equal sized arrays,
    // And merges them into arr[]
    void merge(int* aux, size_t low, size_t mid, size_t high) {
        // Local iterator vars.
        size_t i = low;
        size_t j = mid + 1;

        // Populate aux[]
        for(size_t k = low; k <= high; ++k) {
          aux[k] = arr[k];
        }

        // Iterates through the arrays.
        for(size_t k = low; k <= high; ++k) {
          if(i > mid) {
              render(k, ORANGE);
              render(j, ORANGE);
              delay();
              arr[k] = aux[j++];
          } else if(j > high) {
              render(k, ORANGE);
              render(i, ORANGE);
              delay();
              arr[k] = aux[i++];
          } else if(less(aux[j], aux[i])) {
              render(k, ORANGE);
              render(j, ORANGE);
              delay();
              arr[k] = aux[j++];
          } else {
              render(k, ORANGE);
              render(i, ORANGE);
              delay();
              arr[k] = aux[i++];
          }
        }
    }
};
/*
void Sorter::merge (int a, int b, int c, item * tab []) {
    int i = a, j = b, k = 0 ;
    while ((i < b) && (j < c) && (j < m_size)) {
        BREAKPOINT ;
        if (m_link->cmp_ii(i, j)) {
            tab[a + k++] = m_link->send(i++) ;
        } else {
            tab[a + k++] = m_link->send(j++) ;
        }
    }
    while ((i < b) && (i < m_size)) {
        BREAKPOINT ;
        tab[a + k++] = m_link->send(i++) ;
    }
    for (int h = a; h < j; h++) {
        BREAKPOINT ;
        m_link->receive(h, tab[h]) ;
        m_link->tmpsolve(h) ;
    }
    for (int h = j; (h < c) && (h < m_size); h++) {
        BREAKPOINT ;
        m_link->tmpsolve(h) ;
    }
}
*/
