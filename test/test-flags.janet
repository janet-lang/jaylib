(use jaylib)


(defmacro try-flags-with-fn [fun flags]
    ~(let [[there-were-errors?! result] (protect (,fun ,;flags))]
        (when there-were-errors?!
            (pp result))
        there-were-errors?!))

(defmacro expect-errors [msg fun & flags]
    ~(assert (not (truthy? (try-flags-with-fn ,fun ,flags))) ,msg))

(defmacro no-errors [msg fun & flags]
    ~(assert (try-flags-with-fn ,fun ,flags) ,msg))


(expect-errors
    "wrong flag :foo did not error set-config-flags"
    set-config-flags
    :foo)

(expect-errors
    "wrong flag :foo did not error set-config-flags"
    set-config-flags
    :window-highdpi
    :fullscreen-mode
    :interlaced-hint
    :vsync-hint
    :window-undecorated
    :window-always-run
    :borderless-windowed-mode
    :window-hidden
    :msaa-4x-hint
    :foo
    :window-mouse-passthrough
    :window-resizable
    :window-transparent
    :window-minimized
    :window-unfocused)

(expect-errors
    "wrong flag :foo did not error set-config-flags"
    set-config-flags
    :fullscreen-mode
    :interlaced-hint
    :window-hidden
    :vsync-hint
    :window-always-run
    :window-highdpi
    :borderless-windowed-mode
    :window-maximized
    :msaa-4x-hint
    :foo)

(expect-errors
    "wrong flag :foo did not error set-config-flags"
    set-config-flags
    :foo
    :window-mouse-passthrough
    :window-resizable
    :window-topmost
    :window-transparent
    :window-undecorated
    :window-unfocused)

(no-errors
    "could not set config flags"
    set-config-flags
      :borderless-windowed-mode
      :fullscreen-mode
      :interlaced-hint
      :msaa-4x-hint
      :vsync-hint
      :window-always-run
      :window-hidden
      :window-highdpi
      :window-maximized
      :window-minimized
      :window-mouse-passthrough
      :window-resizable
      :window-topmost
      :window-transparent
      :window-undecorated
      :window-unfocused)

(expect-errors
    "wrong flag did not error rl-matrix-mode"
    rl-matrix-mode :foo)

(no-errors
    "could not set rl-modelview"
    rl-matrix-mode :rl-modelview)

(no-errors
    "could not set rl-projection"
    rl-matrix-mode :rl-projection)

(no-errors
    "could not set rl-texture"
    rl-matrix-mode :rl-texture)