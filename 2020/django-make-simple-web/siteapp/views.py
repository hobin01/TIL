from django.shortcuts import render, get_object_or_404, redirect
from .models import Content, Comment, Recomment, Profile, Board
from django.utils import timezone
from django.core.paginator import Paginator
from django.contrib.auth.models import User
from django.contrib.auth.forms import PasswordChangeForm
from django.contrib.auth.hashers import check_password
from django.contrib.auth import update_session_auth_hash
from django.contrib import messages, auth
from django.template.defaulttags import register
from django.db.models import Q
from .forms import Content_Form
# Create your views here.

def home(request):
  sort = request.GET.get('sort','')
  if sort == 'likes':
    content_list = Content.objects.all().order_by('-like_count','-date')
  elif sort ==  'comments':
    content_list = Content.objects.all().order_by('-comment_count','-date')
  else:
    content_list = Content.objects.all().order_by('-date')
    
  paginator = Paginator(content_list,5)
  page = request.GET.get('page','')
  posts = paginator.get_page(page)
  board = Board.objects.all()
  
  if request.user.is_authenticated:
    user = User.objects.get(id=request.user.id)
    try:
      profile = Profile.objects.get(user_id=user.id)
    except:
      Profile.objects.create(user=user)

  return render(request,'home.html',{'posts':posts, 'Board':board, 'sort':sort})

def search(request):
  content_list = Content.objects.all()
  search = request.GET.get('search','')
  if search:
    search_list = content_list.filter(
      Q(title__icontains = search) | #제목
      Q(body__icontains = search) | #내용
      Q(writer__username__icontains = search) #글쓴이
    )
  paginator = Paginator(search_list,5)
  page = request.GET.get('page','')
  posts = paginator.get_page(page)
  board = Board.objects.all()

  return render(request, 'search.html',{'posts':posts, 'Board':board, 'search':search})

def profile(request):
  profile = Profile.objects.get(user = request.user)
  likes = profile.like_contents.all()
  if request.method=="POST":
    profile.image = request.FILES['Image']
    profile.save()
  return render(request,'profile.html',{'profile':profile, 'likes':likes})

def change_password(request):
  """
  if request.method == "POST":
    form = PasswordChangeForm(request.user, request.POST)
    if form.is_valid():
      user = form.save()
      update_session_auth_hash(request, user)
      messages.success(request, 'Password successfully changed')
      return redirect('profile')
    else:
      messages.error(request, 'Password not changed')
  else:
    form = PasswordChangeForm(request.user)
  return render(request, 'change_password.html',{'form':form})"""

  if request.method == "POST":
    user = request.user
    origin_password = request.POST["origin_password"]
    if check_password(origin_password, user.password):
      new_password = request.POST["new_password"]
      confirm_password = request.POST["confirm_password"]
      if new_password == confirm_password:
        user.set_password(new_password)
        user.save()
        auth.login(request, user, backend='django.contrib.auth.backends.ModelBackend')
        return redirect('profile')
      else:
        messages.error(request, 'Password not same')
    else:
      messages.error(request, 'Password not correct')
    return render(request, 'change_password.html')
  else:
    return render(request, 'change_password.html')

def detail(request, contents_id):
  contents = get_object_or_404(Content, id=contents_id)
  comments = Comment.objects.filter(post = contents_id)

  if (request.method=="POST"):
    comment = Comment()
    comment.body = request.POST['body']
    comment.post = contents
    comment.writer = request.user
    comment.date = timezone.now()
    comment.save()

  recomments = Recomment.objects.all()
  boards = Board.objects.all()
  contents.comment_count = comments.count()
  contents.save()

  return render(request, 'detail.html', {'contents':contents, 'comments':comments, 'recomments':recomments, 'boards':boards})

def create(request):
  global board
  if(request.method=="POST"):
    """contents = Content()
    contents.title = request.POST['Title']
    contents.body = request.POST['Body']
    contents.date = timezone.now()
    contents.writer = request.user
    board = Board.objects.all()
    contents.board = Board.objects.get(id=request.POST['Board'])
    try:
      contents.image = request.FILES['Image']
    except:
      contents.image = None
    contents.save()"""
    board = Board.objects.all()
    form = Content_Form(request.POST, request.FILES)
    if form.is_valid():
      contents = form.save(commit=False)
      contents.board = Board.objects.get(id=request.POST['Board'])
      contents.writer = request.user
      contents = form.save()
    return redirect('/detail/'+str(contents.id),{'Board':board,'form':form})
  else:
    form = Content_Form()
    board = Board.objects.all()
    return render(request,'new.html',{'Board':board,'form':form})

def delete(request, contents_id):
  contents = Content.objects.get(id=contents_id)

  if(request.user == contents.writer):
    contents.delete()
    return redirect('home')
  else:
    return redirect('/detail/'+str(contents.id))

def update(request, contents_id):
  contents = Content.objects.get(id=contents_id)
  global board
  if(request.user ==contents.writer):
    if(request.method=="POST"):
      """contents.title = request.POST['Title']
      contents.body = request.POST['Body']
      contents.date = timezone.now()
      contents.writer = request.user
      board = Board.objects.all()
      contents.board = Board.objects.get(id=request.POST['Board'])
      try:
        contents.image = request.FILES['Image']
      except:
        contents.image = None
      contents.save()"""
      board = Board.objects.all()
      form = Content_Form(request.POST, request.FILES, instance=contents)
      if form.is_valid():
        contents = form.save(commit=False)
        contents.board = Board.objects.get(id=request.POST['Board'])
        contents.writer = request.user
        contents = form.save()
      return redirect('/detail/'+str(contents.id),{'Board':board,'form':form})

    else:
      form = Content_Form(instance=contents)
      board = Board.objects.all()
      return render(request, 'update.html',{'Board':board, 'form':form})

  else:
    board = Board.objects.all()
    return redirect('/detail/'+str(contents.id),{'Board':board})

def comment_delete(request, comment_id):
  comment = Comment.objects.get(id=comment_id)
  contents = Content.objects.get(id=comment.post.id)

  if(request.user == comment.writer):
    comment.delete()
    
    return redirect('/detail/'+str(contents.id))
  else:
    return redirect('/detail/'+str(contents.id))

def recomment(request, comment_id):
  comment = get_object_or_404(Comment, pk=comment_id)
  recomments = Recomment.objects.filter(comment=comment_id)

  if(request.method=="POST"):
    recomment = Recomment()
    recomment.comment = comment
    recomment.body = request.POST['body']
    recomment.writer = request.user
    recomment.date = timezone.now()
    recomment.save()
  
  return redirect('/detail/'+str(comment.post.id), {'recomments':recomments})

def recomment_delete(request, recomment_id):
  recomment = Recomment.objects.get(id=recomment_id)
  if(request.user == recomment.writer):
    recomment.delete()
    return redirect('/detail/'+str(recomment.comment.post.id))
  else:
    return redirect('/detail/'+str(recomment.comment.post.id))

def like(request, contents_id):
  contents = get_object_or_404(Content, id=contents_id)
  user = request.user
  profile = Profile.objects.get(user=user)
  like_contents = profile.like_contents.filter(id=contents_id)

  if like_contents.exists():
    profile.like_contents.remove(contents)
    contents.like_count -= 1
    contents.save()
  else:
    profile.like_contents.add(contents)
    contents.like_count += 1
    contents.save()
  
  return redirect('/detail/'+str(contents.id))

def go_board(request):
  boards = Board.objects.all()
  return render(request,'go_board.html',{'boards':boards})

def board(request,board_id):
  contents = Content.objects.filter(board = board_id)
  paginator = Paginator(contents,3)
  page = request.GET.get('page')
  posts = paginator.get_page(page)
  boards = Board.objects.all()
  now_board = board_id

  return render(request,'board.html',{'posts':posts,'boards':boards,'now_board':now_board})

