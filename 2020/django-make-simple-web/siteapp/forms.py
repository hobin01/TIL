from django import forms
from .models import Content

class Content_Form(forms.ModelForm):
  class Meta:

    model = Content
    fields = ['title','body','image']
  