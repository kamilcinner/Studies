<?php

namespace App\Http\Controllers;

use Illuminate\Http\Request;
use App\Http\Requests\CommentRequest;
use App\Models\Comment;

class CommentsController extends Controller
{
    /**
     * Display a listing of the resource.
     *
     * @return \Illuminate\Http\Response
     */
    public function index()
    {
        $comments = Comment::orderBy('created_at', 'asc')->get();
        return view('comments', compact('comments'));
    }

    /**
     * Show the form for creating a new resource.
     *
     * @return \Illuminate\Http\Response
     */
    public function create()
    {
        $comment = new Comment();
        return view('commentsForm', compact('comment'));
    }

    /**
     * Store a newly created resource in storage.
     *
     * @param  \App\Http\Requests\CommentRequest  $request
     * @return \Illuminate\Http\Response
     */
    public function store(CommentRequest $request)
    {
        $user = auth()->user();
        if (is_null($user)) {
            return view('comments');
        }
        $comment = new Comment();
        $comment->user_id = $user->id;
        $comment->message = $request->message;
        if ($comment->save()) {
            return redirect()->route('comments.index');
        }
        return 'An error has occurred';
    }

    /**
     * Display the specified resource.
     *
     * @param  int  $id
     * @return \Illuminate\Http\Response
     */
    public function show($id)
    {
        //
    }

    /**
     * Show the form for editing the specified resource.
     *
     * @param  int  $id
     * @return \Illuminate\Http\Response
     */
    public function edit($id)
    {
        $comment = Comment::find($id);
        //Sprawdzenie czy użytkownik jest autorem komentarza
        if (\Auth::user()->id != $comment->user_id) {
            return back()->with(['success' => false, 'message_type' => 'danger',
                'message' => 'Nie posiadasz uprawnień do przeprowadzenia tej operacji.']);
        }
        return view('commentsEditForm', compact('comment'));
    }

    /**
     * Update the specified resource in storage.
     *
     * @param  \Illuminate\Http\Request  $request
     * @param  int  $id
     * @return \Illuminate\Http\Response
     */
    public function update(Request $request, $id)
    {
        $comment = Comment::find($id);
        //Sprawdzenie czy użytkownik jest autorem komentarza
        if(\Auth::user()->id != $comment->user_id)
        {
            return back()->with(['success' => false, 'message_type' => 'danger',
                'message' => 'Nie posiadasz uprawnień do przeprowadzenia tej operacji.']);
        }
        $comment->message = $request->message;
        if($comment->save()) {
            return redirect()->route('comments.index');
        }
        return "Wystąpił błąd.";
    }

    /**
     * Remove the specified resource from storage.
     *
     * @param  int  $id
     * @return \Illuminate\Http\Response
     */
    public function destroy($id)
    {
        $comment = Comment::find($id);
        if(\Auth::user()->id != $comment->user_id)
        {
            return back()->with(['success' => false, 'message_type' => 'danger',
                'message' => 'Nie posiadasz uprawnień do przeprowadzenia tej operacji.']);
        }
        if($comment->delete()){
            return redirect()->route('comments.index')->with(['success' => true,
                'message_type' => 'success',
                'message' => 'Pomyślnie skasowano komentarz użytkownika '.
                    $comment->user->name.'.']);
        }
        return back()->with(['success' => false, 'message_type' => 'danger',
            'message' => 'Wystąpił błąd podczas kasowania komentarza użytkownika '.
                $comment->user->name.'. Spróbuj później.']);
    }
}
