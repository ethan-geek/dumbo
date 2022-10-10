LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
					../../Classes/lib_json/json_value.cpp \
					../../Classes/lib_json/json_reader.cpp \
					../../Classes/lib_json/json_writer.cpp\
                   ../../Classes/HelloWorldScene.cpp \
                   ../../Classes/common/AGApplication.cpp \
                   ../../Classes/common/HiHighJsonConvecter.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/game/Background.cpp \
                   ../../Classes/game/GamePlayScene.cpp \
                   ../../Classes/game/Hero.cpp \
                   ../../Classes/model/CoinObject.cpp \
                   ../../Classes/model/FakeFootBarObject.cpp \
                   ../../Classes/model/FootBarObject.cpp \
                   ../../Classes/model/FullCoinItemObject.cpp \
                   ../../Classes/model/HeartInfo.cpp \
                   ../../Classes/model/IAPInfo.cpp \
                   ../../Classes/model/interactionObject.cpp \
                   ../../Classes/model/ItemInfo.cpp \
                   ../../Classes/model/SettingInfo.cpp \
                   ../../Classes/model/StageMapInfo.cpp \
                   ../../Classes/model/StageScoreInfo.cpp \
                   ../../Classes/model/SuperItemObject.cpp \
                   ../../Classes/model/DoubleItemObject.cpp \
                   ../../Classes/model/TrapObject.cpp \
                   ../../Classes/model/SceneManager.cpp \
                   ../../Classes/model/MainPallaxManager.cpp \
                   ../../Classes/model/UserInfo.cpp \
                   ../../Classes/model/UserUpgradeInfo.cpp \
                   ../../Classes/game/ContactListener.cpp \
                   ../../Classes/game/InteractionManager.cpp \
                   ../../Classes/game/ItemTimerManager.cpp \
                   ../../Classes/game/ItemTimer.cpp \
                   ../../Classes/pattern/GroupPattern.cpp \
                   ../../Classes/pattern/Pattern.cpp \
                   ../../Classes/pattern/ResourcePattern.cpp \
                   ../../Classes/pattern/StagePattern.cpp \
                   ../../Classes/common/XmlLoader.cpp \
                   ../../Classes/lib/GLES-Render.cpp \
                   ../../Classes/lib/pugixml.cpp \
                   ../../Classes/common/HiHighAudio.cpp \
                   ../../Classes/common/HHButton.cpp \
                   ../../Classes/common/AGEarthQuakeEffect.cpp \
                   ../../Classes/model/DynamicCoin.cpp \
                   ../../Classes/view/LogoScene.cpp \
                   ../../Classes/view/RankingView.cpp \
                   ../../Classes/view/AbilitiesScene.cpp \
                   ../../Classes/view/MainMenuScene.cpp \
                   ../../Classes/view/BasicPopup.cpp \
                   ../../Classes/view/ClearPopup.cpp \
                   ../../Classes/view/GameLoadingScene.cpp \
                   ../../Classes/view/GameOverPopup.cpp \
                   ../../Classes/view/HeartReqResPopup.cpp \
                   ../../Classes/view/IAPScene.cpp \
                   ../../Classes/view/MessagePopup.cpp \
                   ../../Classes/view/PausePopup.cpp \
                   ../../Classes/view/SettingPopup.cpp \
                   ../../Classes/view/StageInfoPopup.cpp \
                   ../../Classes/view/StageMapScene.cpp \
                   ../../Classes/model/StartItemObject.cpp \
                   ../../Classes/model/ItemObject.cpp \
				   ../../Classes/game/HeroAnimation.cpp \
				   ../../Classes/game/HeroPosition.cpp \
				   ../../Classes/game/HeroStatus.cpp \
				   ../../Classes/view/SlidingMenu.cpp \
				   ../../Classes/common/HeartChecker.cpp \
				   ../../Classes/dao/HiHighDaoSharedUserDefault.cpp \
				   ../../Classes/common/XmlCreator.cpp \
				   ../../Classes/common/AGLog.cpp \
				   ../../Classes/view/HighScoreCell.cpp \
				   ../../Classes/common/HHAlert.cpp \
				   ../../Classes/common/AGUtil.cpp \
				   ../../Classes/common/LogWriterThread.cpp \
				   ../../Classes/helper/AndroidHelper.cpp \
				   ../../Classes/model/WeighItemObject.cpp \
				   ../../Classes/model/AGDeviceInfo.cpp \
				   ../../Classes/model/StarFishObject.cpp \
				   ../../Classes/model/ShieldItemObject.cpp \
				   ../../Classes/model/MagnetItemObject.cpp \
				   ../../Classes/common/HiHighConnector.cpp \
				   ../../Classes/common/HiHighGameData.cpp \
				   ../../Classes/fb/FacebookInterface.cpp \
				   ../../Classes/lib/base64.cpp \
				   ../../Classes/game/GamePlaySceneParts.cpp \
				   ../../Classes/game/GamePlaySceneCore.cpp \
				   ../../Classes/game/BackgroundFlow.cpp \
				   ../../Classes/game/BackgroundFull.cpp \
				   ../../Classes/game/BackgroundSub.cpp \
				   ../../Classes/game/BackgroundManager.cpp \
					../../Classes/network/HHNetworkReceiver.cpp \
					../../Classes/network/HHNetwork.cpp \
					../../Classes/view/CCActivityIndicator.cpp \
					../../Classes/common/HHSecurity.cpp \
#					../libs/libstaticcrypt.a

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

LOCAL_WHOLE_STATIC_LIBRARIES += cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static
LOCAL_WHOLE_STATIC_LIBRARIES += box2d_static
LOCAL_WHOLE_STATIC_LIBRARIES += chipmunk_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_extension_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module,cocos2dx)
$(call import-module,cocos2dx/platform/third_party/android/prebuilt/libcurl)
$(call import-module,CocosDenshion/android)
$(call import-module,extensions)
$(call import-module,external/Box2D)
$(call import-module,external/chipmunk)
