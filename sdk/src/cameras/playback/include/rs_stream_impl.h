// License: Apache 2.0. See LICENSE file in root directory.
// Copyright(c) 2016 Intel Corporation. All Rights Reserved.

#pragma once
#include <memory>
#include <librealsense/rscore.hpp>
#include "include/file_types.h"

namespace rs
{
    namespace playback
    {
        class rs_stream_impl : public rs_stream_interface
        {
        public:
            rs_stream_impl() : m_is_enabled(false) {}
            rs_stream_impl(rs::core::file_types::stream_info &stream_info) : m_stream_info(stream_info), m_is_enabled(false) {}
            void set_frame(std::shared_ptr<rs::core::file_types::frame_sample> &frame) { m_frame = frame;}
            std::shared_ptr<rs::core::file_types::frame_sample> get_frame() { return m_frame; }
            void clear_data() { m_frame.reset(); }
            void set_is_enabled(bool state) { m_is_enabled = state; }
            virtual rs_extrinsics get_extrinsics_to(const rs_stream_interface &r) const override;
            virtual float get_depth_scale() const override { return m_stream_info.profile.depth_scale; }
            virtual rs_intrinsics get_intrinsics() const override { return m_stream_info.profile.intrinsics; }
            virtual rs_intrinsics get_rectified_intrinsics() const override { return m_stream_info.profile.rect_intrinsics; }
            virtual rs_format get_format() const override { return m_stream_info.profile.info.format; }
            virtual int get_framerate() const override { return m_stream_info.profile.frame_rate; }
            virtual int get_frame_number() const override { return m_frame ? m_frame->finfo.number : 0; }
            virtual long long get_frame_system_time() const override { return m_frame ? m_frame->finfo.system_time : 0; }
            virtual const uint8_t *get_frame_data() const override { return m_frame ? m_frame->data : nullptr; }
            virtual int get_mode_count() const override { return get_format() == rs_format::RS_FORMAT_ANY ? 0 : 1; }
            virtual double get_frame_timestamp() const override { return m_frame ? m_frame->finfo.time_stamp : 0; }
            virtual void get_mode(int mode, int *w, int *h, rs_format *f, int *fps) const override;
            virtual bool is_enabled() const override { return m_is_enabled; }
            virtual bool has_data() const { return m_frame ? true : false; }
            rs_stream get_stream_type() { return m_stream_info.stream; }

        private:
            bool                                                m_is_enabled;
            rs::core::file_types::stream_info                   m_stream_info;
            std::shared_ptr<rs::core::file_types::frame_sample> m_frame;
        };
    }
}
