package com.mapbox.mapboxsdk;

import android.annotation.SuppressLint;
import android.content.Context;
import android.content.res.AssetManager;

import androidx.annotation.Keep;
import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.annotation.UiThread;

import com.mapbox.mapboxsdk.constants.MapboxConstants;
import com.mapbox.mapboxsdk.exceptions.MapboxConfigurationException;
import com.mapbox.mapboxsdk.net.ConnectivityReceiver;
import com.mapbox.mapboxsdk.storage.FileSource;
import com.mapbox.mapboxsdk.util.TileServerOptions;
import com.mapbox.mapboxsdk.utils.ThreadUtils;

/**
 * The entry point to initialize the Mapbox Android SDK.
 * <p>
 * Obtain a reference by calling {@link #getInstance(Context, String)}. Usually this class is configured in
 * Application#onCreate() and is responsible for the active access token, application context, and
 * connectivity state.
 * </p>
 */
@UiThread
@SuppressLint("StaticFieldLeak")
@Keep
public final class Mapbox {

  private static final String TAG = "Mbgl-Mapbox";
  private static ModuleProvider moduleProvider;
  private static Mapbox INSTANCE;

  private Context context;
  @Nullable
  private String apiKey;
  @Nullable
  private TileServerOptions tileServerOptions;

  /**
   * Get an instance of Mapbox.
   * <p>
   * This class manages the API key, application context, and connectivity state.
   * </p>
   *
   * @param context Android context which holds or is an application context
   * @param apiKey api key
   * @return the single instance of Mapbox
   */
  @UiThread
  @NonNull
  public static synchronized Mapbox getInstance(@NonNull Context context, @Nullable String apiKey) {
    ThreadUtils.init(context);
    ThreadUtils.checkThread(TAG);
    if (INSTANCE == null) {
      Context appContext = context.getApplicationContext();
      FileSource.initializeFileDirsPaths(appContext);
      INSTANCE = new Mapbox(appContext, apiKey);
      ConnectivityReceiver.instance(appContext);
      INSTANCE.tileServerOptions = TileServerOptions.Default();
    }
    return INSTANCE;
  }

  Mapbox(@NonNull Context context, @Nullable String apiKey) {
    this.context = context;
    this.apiKey = apiKey;
  }

  /**
   * Get the current active access token for this application.
   *
   * @return Mapbox access token
   */
  @Nullable
  public static String getApiKey() {
    validateMapbox();
    return INSTANCE.apiKey;
  }

  /**
   * Set the current active apiKey.
   */
  public static void setApiKey(String apiKey) {
    validateMapbox();
    throwIfApiKeyInvalid(apiKey);
    INSTANCE.apiKey = apiKey;
    FileSource.getInstance(getApplicationContext()).setApiKey(apiKey);
  }

  @Nullable
  public static TileServerOptions getTileServerOptions() {
    return INSTANCE.tileServerOptions;
  }

  /**
   * Application context
   *
   * @return the application context
   */
  @NonNull
  public static Context getApplicationContext() {
    validateMapbox();
    return INSTANCE.context;
  }

  /**
   * Manually sets the connectivity state of the app. This is useful for apps which control their
   * own connectivity state and want to bypass any checks to the ConnectivityManager.
   *
   * @param connected flag to determine the connectivity state, true for connected, false for
   *                  disconnected, and null for ConnectivityManager to determine.
   */
  public static synchronized void setConnected(Boolean connected) {
    validateMapbox();
    ConnectivityReceiver.instance(INSTANCE.context).setConnected(connected);
  }

  /**
   * Determines whether we have an internet connection available. Please do not rely on this
   * method in your apps. This method is used internally by the SDK.
   *
   * @return true if there is an internet connection, false otherwise
   */
  public static synchronized Boolean isConnected() {
    validateMapbox();
    return ConnectivityReceiver.instance(INSTANCE.context).isConnected();
  }

  /**
   * Get the module provider
   *
   * @return moduleProvider
   */
  @NonNull
  public static ModuleProvider getModuleProvider() {
    if (moduleProvider == null) {
      moduleProvider = new ModuleProviderImpl();
    }
    return moduleProvider;
  }

  /**
   * Runtime validation of Mapbox creation.
   */
  private static void validateMapbox() {
    if (INSTANCE == null) {
      throw new MapboxConfigurationException();
    }
  }

  /**
   * Runtime validation of Mapbox access token
   *
   * @param apiKey the access token to validate
   * @return true is valid, false otherwise
   */
  static boolean isApiKeyValid(@Nullable String apiKey) {
    if (apiKey == null) {
      return false;
    }

    apiKey = apiKey.trim().toLowerCase(MapboxConstants.MAPBOX_LOCALE);
    return apiKey.length() != 0;
  }

  /**
   * Throws exception when access token is invalid
   */
  public static void throwIfApiKeyInvalid(@Nullable String apiKey) {
    if (!isApiKeyValid(apiKey)) {
      throw new MapboxConfigurationException(
              "A valid API key is required, currently provided key is: " + apiKey);
    }
  }


  /**
   * Internal use. Check if the {@link Mapbox#INSTANCE} is present.
   */
  public static boolean hasInstance() {
    return INSTANCE != null;
  }

  /**
   * Internal use. Returns AssetManager.
   *
   * @return the asset manager
   */
  private static AssetManager getAssetManager() {
    return getApplicationContext().getResources().getAssets();
  }
}