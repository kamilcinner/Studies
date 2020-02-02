from django import forms

from .models import Product

class ProductForm(forms.ModelForm):
    title       = forms.CharField(label='', widget=forms.TextInput(attrs={'placeholder': 'Your Title'}))
    email       = forms.EmailField()
    description = forms.CharField(
        required=False,
        widget=forms.Textarea(
            attrs={
                'placeholder': 'Your Description',
                'class': 'new-class-name two',
                'id': 'my-id-for-textarea',
                'rows': 20,
                'cols': 12
            }
        ))
    price = forms.DecimalField(initial=100.99)

    class Meta:
        model = Product
        fields = [
            'title',
            'description',
            'price'
        ]

    def clean_title(self, *args, **kwargs):
        title = self.cleaned_data.get('title')
        if 'kamil' not in title:
            raise forms.ValidationError('This is not a valid title')
        if 'news' not in title:
            raise forms.ValidationError('This is not a valid title')
        return title

    def clean_email(self, *args, **kwargs):
        email = self.cleaned_data.get('email')
        if not email.endswith('edu'):
            raise forms.ValidationError('This is not a valid email!')
        return email


class RawProductForm(forms.Form):
    title       = forms.CharField(label='', widget=forms.TextInput(attrs={'placeholder': 'Your Title'})) # required=True is default
    description = forms.CharField(
        required=False,
        widget=forms.Textarea(
            attrs={
                'placeholder': 'Your Description',
                'class': 'new-class-name two',
                'id': 'my-id-for-textarea',
                'rows': 20,
                'cols': 12
            }
        ))
    price       = forms.DecimalField(initial=100.99)