# -*- coding: utf-8 -*-
"""
Created on Sat Jan 23 00:53:00 2021

@author: ghqls
"""

import numpy as np
import sys
sys.path.append('..')
from common.util import preprocess, create_co_matrix, most_similar

text = "You say goodbye and I say hello."
corpus, word_to_id, id_to_word = preprocess(text)
vocab_size = len(word_to_id)
C = create_co_matrix(corpus, vocab_size)

most_similar('say', word_to_id, id_to_word, C)
