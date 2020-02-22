import datetime

from django.contrib.auth.models import User
from django.shortcuts import render, get_object_or_404
from django.urls import reverse_lazy
from django.views import generic

from blog.models import Post, Author, Comment


def index(request):
    """View function for home page of site."""

    # Generate counts of some of the main objects
    num_posts = Post.objects.all().count()
    num_authors = Author.objects.all().count()
    num_comments = Comment.objects.all().count()
    num_users = User.objects.all().count()

    # Number of visits to this view, as counted in the session variable.
    num_visits = request.session.get('num_visits', 0)
    request.session['num_visits'] = num_visits + 1

    context = {
        'num_posts': num_posts,
        'num_authors': num_authors,
        'num_comments':num_comments,
        'num_visits': num_visits,
        'num_users': num_users
    }

    return render(request, 'blog/index.html', context=context)

def user_welcome(request):
    return render(request, 'blog/user_welcome.html', context={})


class AuthorListView(generic.ListView):
    model = Author
    paginate_by = 10


class AuthorDetailView(generic.DetailView):
    model = Author


class PostListView(generic.ListView):
    model = Post
    paginate_by = 10


class PostDetailView(generic.DetailView):
    model = Post


class CommentListView(generic.ListView):
    model = Comment
    paginate_by = 10


class CommentDetailView(generic.DetailView):
    model = Comment


class CommentCreateView(generic.CreateView):
    model = Comment
    fields = ['content']

    def form_valid(self, form):
        """
        Add author and associated post to form data before setting it as valid (so it is saved to model)
        """
        # Add logged-in user as author of comment
        form.instance.author = self.request.user
        # Associate comment with blog based on passed id
        form.instance.post = get_object_or_404(Post, pk=self.kwargs['pk'])
        # Add date today as post date
        form.instance.post_date = datetime.datetime.now()
        # Call super-class form validation behaviour
        return super().form_valid(form)

    def get_success_url(self):
        return reverse_lazy('blog:blog-post-detail', args=[str(self.kwargs['pk'])])

    def get_context_data(self, **kwargs):
        context = super().get_context_data(**kwargs)

        context['post'] = get_object_or_404(Post, pk = self.kwargs['pk'])

        return context
