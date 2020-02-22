from django.urls import path
from . import views


app_name = 'blog'
urlpatterns = [
    path('', views.index, name='index'),

    path('posts/', views.PostListView.as_view(), name='blog-post-list'),
    path('post/<int:pk>', views.PostDetailView.as_view(), name='blog-post-detail'),

    path('bloggers/', views.AuthorListView.as_view(), name='author-list'),
    path('blogger/<int:pk>', views.AuthorDetailView.as_view(), name='author-detail'),

    path('post/<int:pk>/comment/create', views.CommentCreateView.as_view(), name='comment-create'),

    path('welcome/', views.user_welcome, name='user-welcome')
]