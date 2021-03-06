# Provides methods to interact with YouTube playlist items.
# @see https://developers.google.com/youtube/v3/docs/playlistItems
class PlaylistItem
  def delete(options = {})
	do_delete {@id = nil}
	!exists?
  end

  def exists?
	!@id.nil?
  end

private

  def resource_id
	{kind: 'youtube#video', videoId: video_id}
  end

  # @see https://developers.google.com/youtube/v3/docs/playlistItems/update
  def update_parts
	keys = [:position, :playlist_id, :resource_id]
	snippet = {keys: keys, required: true}
	{snippet: snippet}
  end
end
