extern "C" {
  #include <libavcodec/avcodec.h>
  #include <libavformat/avformat.h>
  #include <libavutil/imgutils.h>
}

#include <SDL2/SDL.h>

class Player {
  public:
    Player(SDL_Renderer *engineRenderer, std::string &path);
    ~Player();

    void update();

  private:
    SDL_Texture *texture;
    SDL_Renderer *renderer;
    SDL_Event event;
    AVFrame *frame;
    AVPacket packet;
    AVCodecContext *codecContext;
    AVFormatContext *formatContext = nullptr;
    const AVCodec *videoCodec = nullptr;
    AVCodecParameters *codecParameters = nullptr;
    int videoStreamIndex = -1;

    bool isPlaying = true;
};