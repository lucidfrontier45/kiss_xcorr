'''
Created on Nov 19, 2013

@author: du
'''

import numpy as np

def genPseudoMseq(l=128):
    x = np.ones(l, dtype=np.float32)
    idxes = np.random.randint(0, l, l/2)
    x[idxes] = -1
    return x


def genPseudoMseq2D(h=64, w=64):
    l = h * w
    return genPseudoMseq(l).reshape(h, w)

def fillZero2D(mat, size=(128,128)):
    x = np.zeros(size, dtype=np.float32)
    h, w = mat.shape
    x[0:h, 0:w] = mat
    return x

def embeddMatrix2D(src, dst, x=0, y=0):
    h, w = src.shape
    dst = np.copy(dst)
    dst[:h, :w] = src
    dst = np.roll(dst, x, 0)
    dst = np.roll(dst, y, 1)
    return dst


if __name__ == '__main__':
    import sys
    x = int(sys.argv[1])
    y = int(sys.argv[2])
    
    header_tmp = genPseudoMseq2D(64, 64)
    image = genPseudoMseq2D(128, 128)
    
    image = embeddMatrix2D(header_tmp, image, x, y)
    header_tmp = fillZero2D(header_tmp)
    
    open("header.dat", "wb").write(header_tmp.data)
    open("image.dat", "wb").write(image.data)