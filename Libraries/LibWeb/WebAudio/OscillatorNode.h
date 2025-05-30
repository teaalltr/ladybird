/*
 * Copyright (c) 2024, Shannon Booth <shannon@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <LibWeb/Bindings/OscillatorNodePrototype.h>
#include <LibWeb/WebAudio/AudioScheduledSourceNode.h>

namespace Web::WebAudio {

// https://webaudio.github.io/web-audio-api/#OscillatorOptions
struct OscillatorOptions : AudioNodeOptions {
    Bindings::OscillatorType type { Bindings::OscillatorType::Sine };
    float frequency { 440 };
    float detune { 0 };
    GC::Ptr<PeriodicWave> periodic_wave;
};

// https://webaudio.github.io/web-audio-api/#OscillatorNode
class OscillatorNode : public AudioScheduledSourceNode {
    WEB_PLATFORM_OBJECT(OscillatorNode, AudioScheduledSourceNode);
    GC_DECLARE_ALLOCATOR(OscillatorNode);

public:
    virtual ~OscillatorNode() override;

    static WebIDL::ExceptionOr<GC::Ref<OscillatorNode>> create(JS::Realm&, GC::Ref<BaseAudioContext>, OscillatorOptions const& = {});
    static WebIDL::ExceptionOr<GC::Ref<OscillatorNode>> construct_impl(JS::Realm&, GC::Ref<BaseAudioContext>, OscillatorOptions const& = {});

    Bindings::OscillatorType type() const;
    WebIDL::ExceptionOr<void> set_type(Bindings::OscillatorType);

    void set_periodic_wave(GC::Ptr<PeriodicWave>);

    GC::Ref<AudioParam const> frequency() const { return m_frequency; }
    GC::Ref<AudioParam const> detune() const { return m_detune; }

    WebIDL::UnsignedLong number_of_inputs() override { return 0; }
    WebIDL::UnsignedLong number_of_outputs() override { return 1; }

protected:
    OscillatorNode(JS::Realm&, GC::Ref<BaseAudioContext>, OscillatorOptions const& = {});

    virtual void initialize(JS::Realm&) override;
    virtual void visit_edges(Cell::Visitor&) override;

private:
    // https://webaudio.github.io/web-audio-api/#dom-oscillatornode-type
    Bindings::OscillatorType m_type { Bindings::OscillatorType::Sine };

    // https://webaudio.github.io/web-audio-api/#dom-oscillatornode-frequency
    GC::Ref<AudioParam> m_frequency;

    // https://webaudio.github.io/web-audio-api/#dom-oscillatornode-detune
    GC::Ref<AudioParam> m_detune;

    GC::Ptr<PeriodicWave> m_periodic_wave;
};

}
