from catalog.models import Author, Book, BookInstance, Genre
from django.shortcuts import render
from django.views import generic


def index(request):
    """View function for home page of site."""

    # Generate counts of some of the main objects
    num_books = Book.objects.all().count()
    num_instances = BookInstance.objects.all().count()

    # Available books (status = 'a')
    num_instances_available = BookInstance.objects.filter(status__exact='a').count()

    # The 'all()' is implied by default.
    num_authors = Author.objects.count()

    # Generate count of Genres that contain "fan" in name
    num_fan_contain = Genre.objects.filter(name__icontains='fan').count()

    # Generate count of Books that contain "Wiedźmin" in title
    num_wiedzmin_contain = Book.objects.filter(title__icontains='Wiedźmin').count()

    context = {
        'num_books': num_books,
        'num_instances': num_instances,
        'num_instances_available': num_instances_available,
        'num_authors': num_authors,
        'num_fan_contain': num_fan_contain,
        'num_wiedzmin_contain':  num_wiedzmin_contain
    }

    # Render the HTML template index.html with the data in the context variable
    return render(request, 'catalog/index.html', context=context)


class BookListView(generic.ListView):
    model = Book
    paginate_by = 2


class BookDetailView(generic.DetailView):
    model = Book


class AuthorListView(generic.ListView):
    model = Author
    paginate_by = 1


class AuthorDetailView(generic.DetailView):
    model = Author
