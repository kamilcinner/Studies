import views as views
from django.contrib.auth import authenticate, login
from django.contrib.auth.models import User, Permission
from django.shortcuts import render, get_object_or_404
from django.urls import reverse_lazy
from django.views import generic
from django.views.generic import TemplateView, FormView

from django_registration.forms import UserCreateForm


class UserCreateView(generic.CreateView):
    form_class = UserCreateForm
    template_name = 'auth/user_form.html'

    def get_success_url(self):
        return reverse_lazy('blog:user-welcome')

    def form_valid(self, form):
        # username = form.cleaned_data.get('username')
        # password = form.cleaned_data.get('password')
        # new_user = authenticate(username=username, password=password)
        # login(self.request, new_user)
        #login(self.request, self.object)
        return super().form_valid(form)
