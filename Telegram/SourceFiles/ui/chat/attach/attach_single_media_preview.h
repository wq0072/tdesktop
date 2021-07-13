/*
This file is part of Telegram Desktop,
the official desktop application for the Telegram messaging service.

For license and copyright information please follow this link:
https://github.com/telegramdesktop/tdesktop/blob/master/LEGAL
*/
#pragma once

#include "ui/rp_widget.h"
#include "ui/abstract_button.h"
#include "media/clip/media_clip_reader.h"

namespace Lottie {
class SinglePlayer;
} // namespace Lottie

namespace Ui {

class AttachControlsWidget;
struct PreparedFile;
class IconButton;

class SingleMediaPreview final : public RpWidget {
public:
	static SingleMediaPreview *Create(
		QWidget *parent,
		Fn<bool()> gifPaused,
		const PreparedFile &file);

	SingleMediaPreview(
		QWidget *parent,
		Fn<bool()> gifPaused,
		QImage preview,
		bool animated,
		bool sticker,
		const QString &animatedPreviewPath);
	~SingleMediaPreview();

	[[nodiscard]] rpl::producer<> deleteRequests() const;
	[[nodiscard]] rpl::producer<> editRequests() const;
	[[nodiscard]] rpl::producer<> modifyRequests() const;

private:
	void paintEvent(QPaintEvent *e) override;
	void resizeEvent(QResizeEvent *e) override;

	void preparePreview(
		QImage preview,
		const QString &animatedPreviewPath);
	void prepareAnimatedPreview(const QString &animatedPreviewPath);
	void clipCallback(Media::Clip::Notification notification);

	Fn<bool()> _gifPaused;
	bool _animated = false;
	bool _sticker = false;
	QPixmap _preview;
	int _previewLeft = 0;
	int _previewTop = 0;
	int _previewWidth = 0;
	int _previewHeight = 0;
	Media::Clip::ReaderPointer _gifPreview;
	std::unique_ptr<Lottie::SinglePlayer> _lottiePreview;

	const int _minThumbH;
	const base::unique_qptr<AbstractButton> _photoEditorButton;
	const base::unique_qptr<AttachControlsWidget> _controls;

	rpl::event_stream<> _modifyRequests;

};

} // namespace Ui
