<form role="form" id="comment-form" method="post" enctype="multipart/form-data"
      action="{{ route('comments.update', $comment) }}">
    {{ csrf_field() }}
    <input name="_method" type="hidden" value="PUT">
    <div class="box">
        <div class="box-body">
            <div class="form-group{{ $errors->has('message') ? ' has-error' : '' }}"
                 id="roles_box">
                <label><b>Treść</b></label><br>
                <textarea name="message" id="message" cols="30" rows="10" required>
 {{$comment->message}}
 </textarea>
            </div>
        </div>
    </div>
    <div class="box-footer">
        <button type="submit" class="btn btn-success">Zapisz</button>
    </div>
</form>
