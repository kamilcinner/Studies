from django.contrib.auth.models import User
from django.db import models
from django.urls import reverse


class Author(models.Model):
    name = models.CharField(max_length=20, help_text='Enter your username (max 20 chars).')
    bio = models.TextField(max_length=1000, help_text='Say something about yourself :)')

    def get_absolute_url(self):
        return reverse('blog:author-detail', args=[str(self.id)])

    def __str__(self):
        return self.name


class Post(models.Model):
    class Meta:
        ordering = ['post_date']

    title = models.CharField(max_length=100)
    author = models.ForeignKey('Author', on_delete=models.SET_NULL, null=True)
    post_date = models.DateField()
    content = models.TextField(max_length=500, help_text='Enter your text here.')

    def get_absolute_url(self):
        return reverse('blog:blog-post-detail', args=[str(self.id)])

    def __str__(self):
        return self.title


class Comment(models.Model):
    class Meta:
        ordering = ['post_date']

    author = models.ForeignKey(User, on_delete=models.SET_NULL, null=True)
    post_date = models.DateTimeField()
    post = models.ForeignKey('Post', on_delete=models.SET_NULL, null=True)
    content = models.TextField(max_length=500, help_text='Enter comment about post here.')

    # post/<int:pk>/comment/<int:pk>
    def get_absolute_url(self):
        return reverse('blog:blog-post-detail', args=[str(self.post.id)])

    def __str__(self):
        return f'{self.author.username} ({self.post_date.strftime("%Y-%m-%d %H:%M:%S")}) - {self.content}'
