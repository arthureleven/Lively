#include <iostream>
#include <string>

#include <SDL2/SDL_audio.h>
#include <SDL2/SDL_video.h>

#include <player.hpp>

#define DELAY 1000 / 30

Player::Player(SDL_Renderer *engineRenderer, std::string &path): renderer(engineRenderer) {
  avformat_network_init();

  avformat_open_input(&formatContext, path.c_str(), nullptr, nullptr);
  avformat_find_stream_info(formatContext, nullptr);

  for (unsigned int i = 0; i < formatContext->nb_streams; i++) {
    if (formatContext->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {
      videoStreamIndex = i;
      codecParameters = formatContext->streams[i]->codecpar;
      break;
    }
  }

  if (videoStreamIndex != -1 && codecParameters != nullptr) {
    videoCodec = avcodec_find_decoder(codecParameters->codec_id);

    if (videoCodec) {
      codecContext = avcodec_alloc_context3(videoCodec);

      if (codecContext && avcodec_parameters_to_context(codecContext, codecParameters) >= 0) {
        if (avcodec_open2(codecContext, videoCodec, nullptr) >= 0) {
          frame = av_frame_alloc();

          texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_YV12,
            SDL_TEXTUREACCESS_STREAMING, codecContext->width, codecContext->height);
        }
      }
    }
  }
}

void Player::update() {
  while (av_read_frame(formatContext, &packet) >= 0) {
    if (packet.stream_index == videoStreamIndex) {
      avcodec_send_packet(codecContext, &packet);
      
      while (avcodec_receive_frame(codecContext, frame) == 0) {
        SDL_PollEvent(&event);

        switch (event.type) {
          case SDL_QUIT:
            isPlaying = false;
            break;
          default:
            break;
        }

        if (!isPlaying) {
          return;
        }

        SDL_UpdateYUVTexture(texture, nullptr, frame->data[0], frame->linesize[0],
          frame->data[1], frame->linesize[1], frame->data[2], frame->linesize[2]);
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, nullptr, nullptr);
        SDL_RenderPresent(renderer);
        SDL_Delay(DELAY);
      }
    }
    av_packet_unref(&packet);
  }

  av_seek_frame(formatContext, videoStreamIndex, 0, AVSEEK_FLAG_FRAME);
}

Player::~Player() {
  av_frame_free(&frame);
  avcodec_close(codecContext);
  avformat_close_input(&formatContext);
  avformat_network_deinit();
  SDL_DestroyTexture(texture);
}