# -*- coding: utf-8 -*-
"""
Created on Sat Jan 23 00:36:44 2021

@author: ghqls
"""

import sys
sys.path.append('..')
from common.util import preprocess, create_co_matrix, cos_similarity

text = "You say goodbye and I say hello."
corpus, word_to_id, id_to_word = preprocess(text)
vocab_size = len(word_to_id)
C = create_co_matrix(corpus, vocab_size)

C0 = C[word_to_id['you']]
C1 = C[word_to_id['i']]

print(cos_similarity(C0, C1))